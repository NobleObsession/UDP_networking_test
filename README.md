# UDP_networking_test

## How To Build
1. Clone source project:  
 ` git clone git@github.com:NobleObsession/UDP_networking_test.git `

2. Create build folder near source folder:  
` mkdir build && cd build `

3. Run Conan:  
` conan install ../UDP_networking_test`

4. Run Cmake:  
 ` cmake ../UDP_networking_test `
 
5. Build project  
 `make `
 
 ## How To Run in normal mode
 1. Run server (in one terminal):  
 ` cd build/bin `  
 ` ./UDP_networking_test `
 2. Run python test client (in another terminal):   
 ` python test_client.py `
 3. Then you can find output file:  
 ` build/bin/processed_packets.txt `
 
 ## How To Run in test mode
 1. Run server (in one terminal) with optional argument `test`:  
 ` cd build/bin `  
 ` ./UDP_networking_test test`
 2. Run python test client (in another terminal):   
 ` python test_client.py `
 3. Run script to check output correctness:   
 ` python test_output.py `
 
 
 
   
 
