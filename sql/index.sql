drop database test_index;
create database test_index;

use test_index

create table test_index_table(id int not null,
    `user_id` int not null AUTO_INCREMENT,
    `subject_id` int not null,
    `kind` int not null,
    `action` varchar(100) not null,
    index index_1 (user_id, subject_id, kind, action),
    primary key(id));

describe test_index_table;

show index from test_index_table;

insert into test_index_table(id, user_id, subject_id, kind, action) values(1,1,1,1,"self");
insert into test_index_table(id, user_id, subject_id, kind, action) values(2,1,2,1,"self");
insert into test_index_table(id, user_id, subject_id, kind, action) values(3,1,3,1,"self");
insert into test_index_table(id, user_id, subject_id, kind, action) values(4,2,1,1,"self");
insert into test_index_table(id, user_id, subject_id, kind, action) values(5,2,2,2,"self");
insert into test_index_table(id, user_id, subject_id, kind, action) values(6,2,3,2,"self");
insert into test_index_table(id, user_id, subject_id, kind, action) values(7,3,1,2,"self");
insert into test_index_table(id, user_id, subject_id, kind, action) values(8,3,2,2,"self");

explain select * from test_index_table where user_id = 1 and subject_id = 1 and kind = 1 and action = 'self';
+----+-------------+------------------+------+---------------+---------+---------+-------------------------+------+--------------------------+
| id | select_type | table            | type | possible_keys | key     | key_len | ref                     | rows | Extra                    |
+----+-------------+------------------+------+---------------+---------+---------+-------------------------+------+--------------------------+
|  1 | SIMPLE      | test_index_table | ref  | index_1       | index_1 | 314     | const,const,const,const |    1 | Using where; Using index |
+----+-------------+------------------+------+---------------+---------+---------+-------------------------+------+--------------------------+

explain select * from test_index_table where user_id = 1 and subject_id = 1 and kind = 1;
+----+-------------+------------------+------+---------------+---------+---------+-------------------+------+-------------+
| id | select_type | table            | type | possible_keys | key     | key_len | ref               | rows | Extra       |
+----+-------------+------------------+------+---------------+---------+---------+-------------------+------+-------------+
|  1 | SIMPLE      | test_index_table | ref  | index_1       | index_1 | 12      | const,const,const |    1 | Using index |
+----+-------------+------------------+------+---------------+---------+---------+-------------------+------+-------------+

explain select * from test_index_table where user_id = 1 and subject_id = 1;
+----+-------------+------------------+------+---------------+---------+---------+-------------+------+-------------+
| id | select_type | table            | type | possible_keys | key     | key_len | ref         | rows | Extra       |
+----+-------------+------------------+------+---------------+---------+---------+-------------+------+-------------+
|  1 | SIMPLE      | test_index_table | ref  | index_1       | index_1 | 8       | const,const |    1 | Using index |
+----+-------------+------------------+------+---------------+---------+---------+-------------+------+-------------+

explain select * from test_index_table where user_id = 1;
+----+-------------+------------------+------+---------------+---------+---------+-------+------+-------------+
| id | select_type | table            | type | possible_keys | key     | key_len | ref   | rows | Extra       |
+----+-------------+------------------+------+---------------+---------+---------+-------+------+-------------+
|  1 | SIMPLE      | test_index_table | ref  | index_1       | index_1 | 4       | const |    3 | Using index |
+----+-------------+------------------+------+---------------+---------+---------+-------+------+-------------+

explain select * from test_index_table where user_id = 1 and kind = 1 and action = 'self';
+----+-------------+------------------+------+---------------+---------+---------+-------+------+--------------------------+
| id | select_type | table            | type | possible_keys | key     | key_len | ref   | rows | Extra                    |
+----+-------------+------------------+------+---------------+---------+---------+-------+------+--------------------------+
|  1 | SIMPLE      | test_index_table | ref  | index_1       | index_1 | 4       | const |    3 | Using where; Using index |
+----+-------------+------------------+------+---------------+---------+---------+-------+------+--------------------------+



explain select * from test_index_table where subject_id = 1 and kind = 1 and action = 'self';
+----+-------------+------------------+-------+---------------+---------+---------+------+------+--------------------------+
| id | select_type | table            | type  | possible_keys | key     | key_len | ref  | rows | Extra                    |
+----+-------------+------------------+-------+---------------+---------+---------+------+------+--------------------------+
|  1 | SIMPLE      | test_index_table | index | NULL          | index_1 | 314     | NULL |    8 | Using where; Using index |
+----+-------------+------------------+-------+---------------+---------+---------+------+------+--------------------------+

explain select * from test_index_table where subject_id = 1 and kind = 1 and action = 'self';
+----+-------------+------------------+-------+---------------+---------+---------+------+------+--------------------------+
| id | select_type | table            | type  | possible_keys | key     | key_len | ref  | rows | Extra                    |
+----+-------------+------------------+-------+---------------+---------+---------+------+------+--------------------------+
|  1 | SIMPLE      | test_index_table | index | NULL          | index_1 | 314     | NULL |    8 | Using where; Using index |
+----+-------------+------------------+-------+---------------+---------+---------+------+------+--------------------------+

explain select * from test_index_table where subject_id = 1 and action = 'self';
+----+-------------+------------------+-------+---------------+---------+---------+------+------+--------------------------+
| id | select_type | table            | type  | possible_keys | key     | key_len | ref  | rows | Extra                    |
+----+-------------+------------------+-------+---------------+---------+---------+------+------+--------------------------+
|  1 | SIMPLE      | test_index_table | index | NULL          | index_1 | 314     | NULL |    8 | Using where; Using index |
+----+-------------+------------------+-------+---------------+---------+---------+------+------+--------------------------+

