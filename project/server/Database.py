import sqlite3
import os

DB_PATH = 'database.sqlite3'#המקום בו נשמרת הטבלה

#adhd=[]# [good,miss,more,pushsp,need_posh]
def creation():#creat new database
        if(not os.path.exists(DB_PATH)):
            connection = sqlite3.connect(DB_PATH)
            cursor = connection.cursor()##סמן
            sql_command = """CREATE TABLE Agent(
            num_agent VARCHAR(30),
            sine_pack VARCHAR(30),
            number_of_packets VARCHAR(40),
            avg_psize VARCHAR(20),
            bps VARCHAR(1000),
            ip1 VARCHAR(60),
            ip2 VARCHAR(60),
            port1 VARCHAR(30),
            port2 VARCHAR(30),
            service_type VARCHAR(30),
            time VARCHAR(30)
            );"""
            cursor.execute(sql_command)
            connection.commit()
            cursor = connection.cursor()  
            cursor.close()
            connection.close() 


def newstring(num_agent, sine_pack, number_of_packets, avg_psize, bps, ip1, ip2, port1, port2, service_type, time)##יוצר משתמש חדש במידה והוא לא קיים  במסד  הנתונים ועם הוא קיים שולח מסר בהתאם
    if(check(f'SELECT COUNT(ip1) FROM Users WHERE id="{id}";') is 0):#עובר על הטבלה ובודק האם יש משתמשים מאותה תעודת זהות
        send_command(f'INSERT INTO Users (id,password, name, mail) VALUES ("{id}","{password}", "{name}", "{mail}");')
        return "good"
    else:
        return "heve"

def add_values(name_what_add,idclient,thing_to_add):#מוסיף ערך לרובריקה קיימת
    send_command(f'UPDATE Users SET "{name_what_add}"="{thing_to_add}" WHERE id ="{idclient}";')
    ##command = f'UPDATE INTO Users ("{name_what_add}")="{thing_to_add}" WHERE Country="{idclient}";'
 
def check(command):#בודק את הפעולה הנדרשת בתוך הטבלה ומחזיר את הערך שלה
    connection = sqlite3.connect(DB_PATH)
    conn = connection.cursor()##סמן
    cursor = conn.execute(command)
    connection.commit()
    for row in cursor:
        cursor.close()
        print()
        print(row[0])
        print()
        return (row[0])

def send_command(command):#מבצע את הפעולה שנשלחה בטבלת המשתמשים לפי הפרוטוקול sqlit3
    connection = sqlite3.connect(DB_PATH)
    cursor = connection.cursor()##סמן
    
    try:
       cursor.execute(command)
       connection.commit() 
    except Exception as inst:
         print(type(inst))    # the exception instance
         print(inst.args)     # arguments stored in .args
         print(inst)

def select_all_tasks():#עובר על כל הטבלה
    """
    Query all rows in the tasks table
    :param conn: the Connection object
    :return:
    """
    print("The SQL: ")
    command = "SELECT * FROM Users"
    try:
        cursor.execute(command)
        connection.commit() 
    except Exception as inst:
         print(type(inst))    # the exception instance
         print(inst.args)     # arguments stored in .args
         print(inst)     
 
    rows = cursor.fetchall()

    for row in rows:
        print(row)
