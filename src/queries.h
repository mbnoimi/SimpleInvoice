#ifndef QUERIES_H
#define QUERIES_H

#include <QtCore>

const QString query_table = "SELECT\n"
        "data.id,\n"
        "data.title,\n"
        "data.device,\n"
        "data.description,\n"
        "data.cost,\n"
        "data.recived,\n"
        "data.status,\n"
        "data.note\n"
        "FROM\n"
        "data\n"
        "ORDER BY\n"
        "data.id DESC";

const QString query_devices = "SELECT DISTINCT\n"
        "data.device\n"
        "FROM\n"
        "data\n"
        "ORDER BY\n"
        "data.id DESC";

const QString query_statues = "SELECT DISTINCT\n"
        "data.status\n"
        "FROM\n"
        "data\n"
        "ORDER BY\n"
        "data.id DESC";

const QString query_filters = "SELECT\n"
        "data.id,\n"
        "data.title,\n"
        "data.device,\n"
        "data.description,\n"
        "data.cost,\n"
        "data.recived,\n"
        "data.status,\n"
        "data.note\n"
        "FROM\n"
        "data\n"
        "WHERE\n"
        "data.%1 LIKE \"%2\"\n"
        "ORDER BY\n"
        "data.id DESC";

const QString query_add = "INSERT INTO \"main\".\"data\" (\"title\", \"device\", \"description\", \"cost\", \"recived\", \"note\", \"model\", \"serial\", \"sent\", \"phone\", \"status\") VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11')";
const QString query_update = "UPDATE \"main\".\"data\" SET \"title\"='%1', \"device\"='%2', \"description\"='%3', \"cost\"='%4', \"recived\"='%5', \"note\"='%6', \"model\"='%7', \"serial\"='%8', \"sent\"='%9', \"phone\"='%10', \"status\"='%11' WHERE (\"id\"='%12')";

const QString query_update_load = "SELECT\n"
        "data.id,\n"
        "data.title,\n"
        "data.device,\n"
        "data.cost,\n"
        "data.description,\n"
        "data.recived,\n"
        "data.model,\n"
        "data.note,\n"
        "data.serial,\n"
        "data.sent,\n"
        "data.phone,\n"
        "data.status\n"
        "FROM\n"
        "data\n"
        "WHERE\n"
        "data.id = %1";
const QString query_delete = "DELETE FROM \"main\".\"data\" WHERE (\"id\"=%1)";

#endif // QUERIES_H
