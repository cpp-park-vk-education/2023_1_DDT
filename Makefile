generate:
	mkdir build
	cmake -B build/
	
build-project:
	cd ./build && make

clean:
	rm -rf build

rebuild: clean generate build-project

server-run:
	./build/server/internal/httpServer/HttpServer_run

test:
	ctest --verbose --output-on-failure --test-dir  build/

check:
	cppcheck server --std=c++17 --enable=all

lint:
	cpplint --extensions=cpp,hpp,h --recursive ./server/* ./client/*


dev:
	docker run --rm -it \
		-v $(PWD):/project \
		--name app \
		-p 8080:8080 \
		raiden454/cpp-app

stop-docker:
	docker stop app

run-docker-compose:
	docker compose down --volumes
	docker compose up -d --build