// Example code based upon http://www.kitebird.com/mysql-book/ch06-3ed.pdf
//
// run as ./conntest -h localhost -p -u siewerts
//
// Using your MySQL username and enter your password when prompted
//

#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <my_sys.h>
#include <m_string.h>
#include <mysql.h>
#include <my_getopt.h>


static unsigned int opt_port_num = 0; /* port number (use built-in value) */
static char *opt_socket_name = NULL; /* socket name (use built-in value) */
static unsigned int opt_flags = 0; /* connection flags (none) */
static char *opt_host_name = NULL; /* server host (default=localhost) */
static char *opt_user_name = NULL; /* username (default=login name) */
static char *opt_password = NULL; /* password (default=none) */
static char *opt_db_name = NULL; /* database name (default=none) */


static int ask_password = 0;          /* whether to solicit password */
static MYSQL *conn; /* pointer to connection handler */
static const char *client_groups[] = { "client", NULL };

static struct my_option my_opts[] =   /* option information structures */
{
  {"help", '?', "Display this help and exit",
  NULL, NULL, NULL,
  GET_NO_ARG, NO_ARG, 0, 0, 0, 0, 0, 0},
  {"host", 'h', "Host to connect to",
  (uchar **) &opt_host_name, NULL, NULL,
  GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"password", 'p', "Password",
  (uchar **) &opt_password, NULL, NULL,
  GET_STR, OPT_ARG, 0, 0, 0, 0, 0, 0},
  {"port", 'P', "Port number",
  (uchar **) &opt_port_num, NULL, NULL,
  GET_UINT, REQUIRED_ARG, 0, 
 0, 0, 0, 0, 0},
  {"socket", 'S', "Socket path",
  (uchar **) &opt_socket_name, NULL, NULL,
  GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"user", 'u', "User name",
  (uchar **) &opt_user_name, NULL, NULL,
  GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  { NULL, 0, NULL, NULL, NULL, NULL, GET_NO_ARG, NO_ARG, 0, 0, 0, 0, 0, 0 }
};


void print_error(MYSQL* conn, char* message)
{
    fprintf(stderr, "%s\n", message);
    if (conn != NULL)
    {
      fprintf(stderr, "Error %u (%s)\n", mysql_errno(conn), mysql_error(conn));
    }
}


void process_result_set (MYSQL *conn, MYSQL_RES *res_set)
{
    MYSQL_ROW row;
    unsigned int i;

    while ((row = mysql_fetch_row (res_set)) != NULL)
    {

        for (i = 0; i < mysql_num_fields (res_set); i++)
        {
            if (i > 0)
                fputc ('\t', stdout);
            printf ("%s", row[i] != NULL ? row[i] : "NULL");
        }
        fputc ('\n', stdout);
    }

    if (mysql_errno (conn) != 0)
        print_error (conn, "mysql_fetch_row() failed");
    else
        printf ("%lu rows returned\n", (unsigned long) mysql_num_rows (res_set));
}



void process_real_statement (MYSQL *conn, char *stmt_str, unsigned int len)
{

    MYSQL_RES *res_set;

    if (mysql_real_query (conn, stmt_str, len) != 0) /* the statement failed */
    {
        print_error (conn, "Could not execute statement");
        return;
    }


    /* the statement succeeded; determine whether it returned data */
    res_set = mysql_use_result (conn);

    if (res_set) /* a result set was returned */
    {
        /* process rows and then free the result set */
        process_result_set (conn, res_set);
        mysql_free_result (res_set);
    }
    else /* no result set was returned */
    {
        /*
         * * does the lack of a result set mean that the statement didn't
         * * return one, or that it should have but an error occurred?
         * */
        if (mysql_errno (conn) == 0)
        {
            /*
             * * statement generated no result set (it was not a SELECT,
             * * SHOW, DESCRIBE, etc.); just report rows-affected value.
             * */
            printf ("%lu rows affected\n", (unsigned long) mysql_affected_rows (conn));
        }
        else /* an error occurred */
        {
            print_error (conn, "Could not retrieve result set");
        }
    }
}


static my_bool
get_one_option (int optid, const struct my_option *opt, char *argument)
{
  switch (optid)
  {
  case '?':
    //my_print_help(my_opts);  /* print help message */
    exit (0);
  case 'p':                   /* password */
    if (!argument)            /* no value given; solicit it later */
      ask_password = 1;
    else                      /* copy password, overwrite original */
    {
      opt_password = strdup (argument);
      if (opt_password == NULL)
      {
        print_error (NULL, "could not allocate password buffer");
        exit (1);
      }
      while (*argument)
        *argument++ = 'x';
      ask_password = 0;
    }
    break;
  }
  return(0);
}


int main(int argc, char **argv)
{
    MYSQL_RES *res_set;

    int opt_err;
    //MY_INIT (argv[0]);

    //load_defaults("my", client_groups, &argc, &argv);

    if ((opt_err = handle_options (&argc, &argv, my_opts, get_one_option)))
      exit (opt_err);

    /* solicit password if necessary */
    if (ask_password)
      opt_password = get_tty_password (NULL);

    /* get database *  name if present on command line */
    if (argc > 0)
    {
      opt_db_name = argv[0];
     --argc; ++argv;
    }

    /* initialize client library */
    if (mysql_library_init (0, NULL, NULL))
    {
      print_error (NULL, "mysql_library_init() failed");
      exit (1);
    }

    /* initialize connection handler */
    conn = mysql_init (NULL);
    if (conn == NULL)
    {
        fprintf (stderr, "mysql_init() failed (probably out of memory)\n");
        exit (1);
    }


    /* connect to server */

    printf("connecting to server with host=%s, user=%s, pass=%s, db_name=%s, port_num=%d, socket_name=%s, flags=0x%x\n",
           opt_host_name, opt_user_name, opt_db_name, opt_password, opt_port_num, opt_socket_name, opt_flags);

    if (mysql_real_connect (conn, opt_host_name, opt_user_name, opt_password, opt_db_name, opt_port_num, opt_socket_name, opt_flags) == NULL)
    {
        fprintf (stderr, "mysql_real_connect() failed\n");
        mysql_close (conn);
        exit (1);
    }


    /* simple stand-alone example
    if (mysql_query (conn, "SELECT 'sakila'") != 0)
    {
        print_error (conn, "SELECT statement failed");
    }
    else
    {
        printf ("SELECT statement succeeded\n");
    }
    res_set = mysql_use_result (conn);
    mysql_free_result (res_set);

*/
    if (mysql_query (conn, "USE sakila") != 0)
    {
        print_error (conn, "SELECT statement failed");
    }
    else
    {
        printf ("SELECT statement succeeded\n");
    }
    res_set = mysql_use_result (conn);
    mysql_free_result (res_set);


    process_real_statement (conn, "SHOW TABLES", 12);
    process_real_statement (conn, "describe film", 14);

    /* disconnect from server */
    mysql_close (conn);
    exit (0);

}

