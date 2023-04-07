if [ "$1" = "clean" ]; then
  rm -rf build
fi

if [ ! -d build ]; then
  mkdir build
fi

cd build
cmake .. -GNinja
ninja
./Pendulum