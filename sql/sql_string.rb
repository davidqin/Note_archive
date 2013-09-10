bash_sql = "explain select * from test_index_table where "

where_conditions = [ "user_id = 1",
                     "subject_id = 1",
                     "kind = 1",
                     "action = 'self'"
                   ]

result = `mysql -uroot -proot test_index -e #{bash_sql} #{where_conditions.join(' and ')}`
puts result