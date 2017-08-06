#ifndef MYSQL_OPERATOR_H
#define MYSQL_OPERATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#ifdef WINDOWS
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

#include "MyConfig.h"

#define HOST "localhost"
#define PORT "3306"
#define USER "root"
#define PASSWORD  "huwei351"
#ifdef DLT
#define DATABASE "dlt"
#else
#define DATABASE "ssq"
#endif
#define CHARSET "utf8"

#define TABLE_SSQ "ssq_result"
#define TABLE_DLT "dlt_result"

#define FIELD_RID "rid"
#define FIELD_DATE "date"
#define FIELD_RB_FIRST "rb1"
#define FIELD_RB_SECOND "rb2"
#define FIELD_RB_THIRD "rb3"
#define FIELD_RB_FOURTH "rb4"
#define FIELD_RB_FIFTH "rb5"
#define FIELD_RB_SIXTH "rb6"
#ifdef DLT
#define FIELD_BB1 "bb1"
#else
#define FIELD_BB1 "bb"
#endif
#define FIELD_BB2 "bb2"

#define ROW_G "\n"
#define COLUMN_G ","
#define CR_G ",\n"


class MySqlOperator
{
    public:

        MYSQL mysql;

        MySqlOperator(MyConfig *myconfig) {
            mMyConfig = myconfig;
        }

        ~MySqlOperator() {
            delete mMyConfig;
        }


        int ConnMySQL(char *host, char * port, char * Db, char * user, char* passwd, char * charset);

        std::string SelectData(char * table, char * field, int rmax, char *order = "DESC");

        int InsertData(char * table, char * v_rid, char * v_date, char * v_rb1, char * v_rb2, char * v_rb3, char * v_rb4, char * v_rb5, char * v_rb6, char * v_bb);

        int UpdateData(char * table, char * field, char * value, char * w_field, char * w_value);

        int DeleteData(char * table, char * field, char * value);

        void CloseMySQLConn();

    private:

        MyConfig *mMyConfig;

};

#endif
