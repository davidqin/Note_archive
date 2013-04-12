require "rack"

Rack::Server.new(app: Rack::Directory.new("~/")).start