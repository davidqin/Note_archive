浏览器端缓存：

缓存协商

最后修改时间

相应头中带有Last-Modified: 时间
请求头中带有If-Modified-Since: 时间

返回304，使用本地浏览器缓存

etag
根据内容的协商策略
适用于，文件经常被修改，修改时间总变化，但是内容不变

Expires 时间（时刻）
过期时间，在这时间内，无需询问web服务器是否更新，直接使用本地缓存

Ctrl+F5 不使用任何缓存协商

F5 Last-modified生效 expires无效

点击url expires生效

Cache-Control: max-age=<second> 时间（时间间隔）
很类似expires，就是时间格式不同

Http是浏览器和web服务器沟通的语言，唯一的沟通方法，无论多复杂的沟通，本质都体现在http中。但是是很多人往往忽略了对于http的深入理解和学习，而是被一些包在他们外面的东西所蒙蔽，虽然这些东西可以让我们快速上手，但是你将永远不知道真相。