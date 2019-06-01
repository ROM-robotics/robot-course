sudo apt-get install ros-kinetic-kobuki-gazebo-plugins
sudo apt-get install ros-kinetic-yocs-cmd-vel-mux
sudo apt-get install ros-kinetic-slam-gmapping
sudo apt-get install ros-kinetitc-navigation

change this in amcl_demo.launch
<node name="map_server" pkg="map_server" type="map_server" args="$(arg map_file)" />
	<br> OR <br>
  <node name="map_server" pkg="map_server" type="map_server"/>
