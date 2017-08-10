MVCGame
=====================

MVCGame strives to be a MVC Game engine
using all the neat features of the C++11 standard.

fork from github.com/respu/mvcgame

Guidelines
----------

* no naked pointers (use std::unique_ptr and std::shared_ptr)
* no polymorphism (use std::function and std::bind as a substitute for delegates)
* try not to do any casting
