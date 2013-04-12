require "rack"

class Static
  def self.call env
    resource = env["PATH_INFO"] =~ /\/$/ ? ["index.html"] : ["static", env["PATH_INFO"]]
    path = File.join("public", *resource)
    type = resource.last.end_with?("html") ? "html" : "plain"
    if File.exist?(path)
      ["200", {"Content-Type" => "text/#{type}"}, File.read(path)]
    else
      ["200", {"location" => "text/plain"}, ["ok"]]
    end
  end
end

Rack::Server.new(app: Static).start
