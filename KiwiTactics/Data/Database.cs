using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SQLite;
namespace KiwiTactics.Data
{
    internal class Database
    {
        public bool NewDatabaseFile()
        {
            if (File.Exists("database.db"))
            {
                return true;
            }
            try
            {
                SQLiteConnection sqliteConn = new SQLiteConnection("database.db");
                return true;
            }
            catch (Exception e)
            {
                throw new Exception("create new database file database.db fail: " + e.Message);
            }
        }

        void CreateTable()
        { 
            SQLiteConnection sqliteConn = new SQLiteConnection("data source=database.db");
            if (sqliteConn.State != System.Data.ConnectionState.Open) 
            { 
                sqliteConn.Open();
                SQLiteCommand cmd = new SQLiteCommand();
                cmd.Connection = sqliteConn;
                // 创建所需要的核心表
                cmd.CommandText = "CREATE TABLE Building ()";
                cmd.ExecuteNonQuery();
                cmd.CommandText = "CREATE TABLE Building ()";
                cmd.ExecuteNonQuery();
                cmd.CommandText = "CREATE TABLE Building ()";
                cmd.ExecuteNonQuery();
                cmd.CommandText = "CREATE TABLE Building ()";
                cmd.ExecuteNonQuery();
            }
            sqliteConn.Close();
        }

    }
}
