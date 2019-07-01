# Map_My_World
##first step:   creat a catkin workspace
             
              $ mkdir -p catkin_ws/src
	            $ cd catkin_ws/src

              $ catkin_init_workspace
              $ cd ..
              $ catkin_make

              $ cd src
              
##second step:
            
	       $ git clone https://github.com/ymiaoy/Map_My_World
              
              $ cd catkin_ws
              $ catkin_make
              
              (if you didn't add workspace's path to bashrc, you should also do this:
                   $ source devel/setup.bash
              )
 
##third step: 
       
         $ roslaunch location world.launch    
         $ roslaunch location teleop.launch
         
         $ roslaunch location localization.launch
##final step:
         $  rtabmap-databaseViewer rtabmap.db


## note:
       rtabmap.db file has been stored in the following:


       链接: https://pan.baidu.com/s/106xud5jsb_-SYymqUUM_gw 
       提取码: vm22 
              
              
