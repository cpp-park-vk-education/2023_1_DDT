generate:
	mkdir build
	cmake -B build/
	
build-project:
	cd ./build && make

clean:
	rm -rf build

rebuild: clean generate build-project

server-run:
	./build/server/cmd/Server

test:
	ctest --verbose --output-on-failure --test-dir  build/

dev:
	docker run --rm -it \
		-v $(PWD):/project \
		--name app \
		raiden454/cpp-app

stop-docker:
	docker stop app



