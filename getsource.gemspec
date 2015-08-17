require 'rake'

Gem::Specification.new do |s|
  s.name = 'getsource'
  s.version = '0.2.2'
  s.author = 'Dario Seminara'
  s.email = 'robertodarioseminara@gmail.com'
  s.platform = Gem::Platform::RUBY
  s.summary = 'Get the source file path of the implementation of a given method'
  s.homepage = "http://github.com/tario/getsource"
  s.has_rdoc = true
  s.extra_rdoc_files = [ 'README' ]
  s.rdoc_options << '--main' << 'README'
  s.extensions = FileList["ext/**/extconf.rb"].to_a
  s.files = Dir.glob("{examples,lib,test}/**/*.rb") + Dir.glob("ext/**/*.c") + Dir.glob("ext/**/*.h") + Dir.glob("ext/**/extconf.rb") +
      [ 'AUTHORS', 'CHANGELOG', 'README', 'Rakefile', 'TODO' ]
end