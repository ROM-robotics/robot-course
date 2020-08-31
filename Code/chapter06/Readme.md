sudo apt upgrade

Install this pkgs <br>
****************** <br>
sudo apt-get install ros-kinetic-kobuki-gazebo-plugins <br>
sudo apt-get install ros-kinetic-yocs-cmd-vel-mux <br>
sudo apt-get install ros-kinetic-slam-gmapping <br>
sudo apt-get install ros-kinetitc-navigation <br>

change this in amcl_demo.launch
********************************
<br>
"&lt node name='map_server' pkg='map_server' type='map_server' args='$(arg map_file)' / &gt"
	<br> OR <br>
 "&lt node name='map_server' pkg='map_server' type='map_server'/&gt" 
