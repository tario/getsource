require 'mkmf'
dir_config('getsource_base')
MakeMakefile::CONFIG['CC'] = ENV['CC'] or 'gcc'

ruby_version = MakeMakefile::CONFIG["ruby_version"]
ruby_version = ruby_version.split(".")[0..1].join(".")

if ruby_version == "1.8"
	$CFLAGS = $CFLAGS + " -DRUBY1_8"
elsif ruby_version == "1.9"
	$CFLAGS = $CFLAGS + " -DRUBY1_9"
elsif ruby_version == "2.2"
	$CFLAGS = $CFLAGS + " -DRUBY2_2"
end

$CFLAGS = $CFLAGS  + " -o $@"

create_makefile('getsource_base')



