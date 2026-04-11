# practicing-cpp-mini-redis
Practicing C++ by building a trimmed down version of Redis.

## Supported commands
- `SET key value`
- `GET key`
- `DEL key`
- `KEYS`

## Build and run
```bash
chmod +x build.sh
./build.sh
```

Server starts on port 6380.

## Connect
```bash
redis-cli -p 6380
```

## What's in scope
- TCP server with RESP protocol parsing
- In-memory key-value store
- Thread-safe concurrent client handling
- Key expiration with TTL

## Out of scope
- Persistence (no RDB/AOF)
- Pub/sub
- Data types beyond strings
- Replication
- Pipelining