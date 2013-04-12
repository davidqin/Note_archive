require "rack"

class StaticRack
  def self.call env
    ["200", {"Content-Type" => "text/plain"}, ["none static resource"]]
  end
end

Rack::Server.new(
  app: Rack::Static.new(StaticRack, urls: ["/static"], root: 'public', index: "index.html")
).start