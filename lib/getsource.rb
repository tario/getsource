=begin

This file is part of the getsource project, http://github.com/tario/getsource

Copyright (c) 2010 Roberto Dario Seminara <robertodarioseminara@gmail.com>

getsource is free software: you can redistribute it and/or modify
it under the terms of the gnu general public license as published by
the free software foundation, either version 3 of the license, or
(at your option) any later version.

getsource is distributed in the hope that it will be useful,
but without any warranty; without even the implied warranty of
merchantability or fitness for a particular purpose.  see the
gnu general public license for more details.

you should have received a copy of the gnu general public license
along with getsource.  if not, see <http://www.gnu.org/licenses/>.

=end
require "getsource_base"

class Method

  class Node

    attr_reader :file
    attr_reader :line

    def initialize(file_,line_)
      @file = file_
      @line = line_
    end
  end

  begin
    instance_method("body")
  rescue
    def body
      if source_location
        Method::Node.new(source_location[0], source_location[1])
      else
        Method::Node.new("",0)
      end
    end
  end
end

class UnboundMethod
  begin
    instance_method("body")
  rescue
    def body
      if source_location
        Method::Node.new(source_location[0], source_location[1])
      else
        Method::Node.new("",0)
      end
    end
  end
end


class Object

  def specific_method(arg1, arg2=nil)
    if arg2
      method_name = arg2
      klass = arg1

      if instance_of? Class
        method(method_name)
      else
        klass.instance_method(method_name).bind(self)
      end
    else
      method(arg1)
    end
  end
end
