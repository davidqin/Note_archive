server = TCPServer.open('127.0.0.1',2000)

client = server.accept

loop {
    str=client.gets
    puts str
    client.puts(str)
}
client.close
