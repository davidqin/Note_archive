host = '127.0.0.1'
port = 2000
msg="\0x48\0x0a\0x0d"
s = TCPSocket.open(host, port)
s.setsockopt(Socket::IPPROTO_TCP, Socket::TCP_NODELAY, 1)
loop  do
    s.puts(msg)
    s.flush
    puts msg
    resp = s.gets
    puts resp
    sleep 1
end
