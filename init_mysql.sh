docker run -d --name my-mysql \
  -p 3306:3306 \
  -e MYSQL_ROOT_PASSWORD=123456 \
  -e MYSQL_TCP_PORT=3306 \
  -v "$PWD/init.sql":/docker-entrypoint-initdb.d/01-init.sql:ro \
  -e TZ=Asia/Singapore \
  mysql:8.0 \
  --character-set-server=utf8mb4 \
  --collation-server=utf8mb4_general_ci
