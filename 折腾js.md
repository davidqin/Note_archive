需求
---

想弄个后端基于 sinatra 前端 spine.js + websocket 的html5游戏大厅

组织前端代码的时候，我开始了漫长的折腾！

经过
---


##### 选方案

在commonjs和AMD上徘徊了好久，决定用AMD规范。了解了下require.js，感觉有些复杂，选择了一个替代品，[Do.js](https://github.com/kejun/Do)。

##### 问题出现

不习惯，也不喜欢这种模块定义，处理各种ready，各种依赖，很头疼。而且请求数量很多，换！

##### 决定使用commonjs

commonjs的代码组织方式和ruby很像，用什么require什么，同步加载，而且请求数量很少。开始了一顿search，目光首先被[hem](https://github.com/spine/hem)吸引。这个是sqinejs作者写的，和sqine都是一套的东西，用起来应该会很不错。

##### hem

开发时候需要启动hem服务器，依赖nodejs，部署的时候生成静态文件，自带测试框架。

##### 问题出现

没整明白，开始怀念rails的assets pipeline。用rails的想法油然而生，还好控制住了。

##### 开始search rails assets pipeline。

发现rails也是依赖gem，[sprockets](https://github.com/sstephenson/sprockets), 大喜。开始search sprockets。

##### sprockets 与 sinatra 整合

经过search和尝试，最终决定用middleware方式解决。顺利的在application.js加载所有js。

##### 问题出现

犹豫所有的js都在application.js文件中，不方便debug。回想到rails的javascript_include_tag方法，development模式下分开加载所有js文件, production模式下只加载整合过的一个js文件。再一次怀念rails。寻找gem，发现[alphasights-sinatra-sprockets](https://github.com/alphasights/sinatra-sprockets/blob/master/lib/sinatra/sprockets.rb)。

##### alphasights-sinatra-sprockets

集成sprockets于sinatra的gem，包括helper。

##### 问题出现

修改了之前的middleware，发现错误，缺少js与css compiler。
并且也没有找到如何让其分开加载js文件。

未完待续