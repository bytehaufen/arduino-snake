init: 
	pio project init --board=uno --ide=vim
	pio project init --board=uno --ide=vscode
build:
	pio run -t compiledb
	pio run -t upload
	pio device monitor
update:
	pio run -t compiledb
monitor:
	pio device monitor
clean:
	pio run -t clean
