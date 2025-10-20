docker exec -i ai-httpserver-2 sh -lc '
  DBS=$(mysql --protocol=TCP -h 127.0.0.1 -P 3306 -uroot -p123456 -Nse "
    SELECT SCHEMA_NAME
    FROM INFORMATION_SCHEMA.SCHEMATA
    WHERE SCHEMA_NAME NOT IN (\"mysql\",\"sys\",\"information_schema\",\"performance_schema\");
  ");
  mysqldump --protocol=TCP -h 127.0.0.1 -P 3306 \
    -uroot -p123456 \
    --no-data \
    --routines --triggers --events \
    --default-character-set=utf8mb4 \
    --add-drop-database --add-drop-table \
    --set-gtid-purged=OFF \
    --databases $DBS
' > ./initdb.sql
