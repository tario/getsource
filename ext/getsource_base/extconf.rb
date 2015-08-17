require 'mkmf'
dir_config('getsource_base')

config_module = %w(1.8, 1.9, 2.0, 2.1).include?(ruby_version) ? Config : MakeMakefile 

config_module::CONFIG['CC'] = 'gcc'

ruby_version = config_module::CONFIG["ruby_version"]
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



