# Makfile for converting mermaid diagrams into images
# 
# Output files can be found in: images/
.PHONY: all

all: images/classdiagram.png images/sequencediagram.png

images/classdiagram.png: assets/classdiagram.md assets/mermaid.json
	docker run --rm -u `id -u`:`id -g` -v $$PWD:/data minlag/mermaid-cli:latest -p assets/puppeteer-config.json --configFile assets/mermaid.json -i assets/classdiagram.md -o images/classdiagram.png --scale 10 -b transparent
	rm -f images/classdiagram.png
	mv images/classdiagram-1.png images/classdiagram.png

images/sequencediagram.png: assets/sequencediagram.md assets/mermaid.json
	docker run --rm -u `id -u`:`id -g` -v $$PWD:/data minlag/mermaid-cli:latest -p assets/puppeteer-config.json --configFile assets/mermaid.json -i assets/sequencediagram.md -o images/sequencediagram.png --scale 10 -b transparent
	rm -f images/sequencediagram.png
	mv images/sequencediagram-1.png images/sequencediagram.png

