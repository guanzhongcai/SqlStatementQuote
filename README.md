# SqlStatementQuote
给SQL语句中的字段名和表名添加双引号

## example

把sql语句中的字段名和表名：
``` sql
select Id, PatientName from Person where "Id"=:id
```
添加双引号：
``` sql
select "Id", "PatientName" from "Person" where "Id"=:id
```

在使用[soci](http://soci.sourceforge.net/doc/release/4.0/)项目访问postgresql时，因为后者是大小写敏感的，所以sql语句中字段名和表名需要添加双引号。为了解决编码过程中不需要写很多\"的转义字符，封装了此wrapper类.
