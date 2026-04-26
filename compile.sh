if [[ "$1" == "clean" ]]; then
    rm -rf build
fi
cmake -S . -B build -DBUILD_LEVEL=platform -DBUILD_DEMOS=ON -DBUILD_TESTING=OFF
cmake --build build