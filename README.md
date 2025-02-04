
# 3D Visualization Server

Get the repository
```bash
git clone git@github.com:Eryk-Mozdzen/visualization-3d.git
cd visualization-3d
```

Create build directory and build server executable
```bash
mkdir build
cd build
cmake ..
make
```

Run server
```bash
./server
Starting listening on localhost port 8080
```

To test if server is working, run example client in separate terminal
```bash
python3 example.py
```
