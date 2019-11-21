#! /usr/bin/env python

import sys
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg

moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface_tutorial', anonymous=True)

robot = moveit_commander.RobotCommander()
scene = moveit_commander.PlanningSceneInterface()
group1 = moveit_commander.MoveGroupCommander("arm")
end_effector_link1 = group1.get_end_effector_link()

"""
reference_frame = 'base_link'
arm.set_pose_reference_frame(reference_frame)


arm.allow_replanning(True)
        

arm.set_goal_position_tolerance(0.01)
arm.set_goal_orientation_tolerance(0.05)
"""

#group.set_goal_joint_tolerance(10)

display_trajectory_publisher = rospy.Publisher(
    '/move_group/display_planned_path', moveit_msgs.msg.DisplayTrajectory, queue_size=1)

print "Robot Groups:"
print robot.get_group_names()

pose_target = geometry_msgs.msg.Pose()
joint_positions1 = geometry_msgs.msg.Pose()
joint_positions2 = geometry_msgs.msg.Pose()


"""
pose_target.orientation.x = 0.5574
pose_target.orientation.y = -0.3162
pose_target.orientation.z = 0.6823
pose_target.orientation.w = 0.3518

pose_target.position.x = -0.1957
pose_target.position.y = 1.1788
pose_target.position.z = 0.5712
group.set_pose_target(pose_target)

plan1 = group.plan()

rospy.sleep(5)
"""

"""
group.set_named_target('long')
plan1 = group.plan()
rospy.sleep(5)
group.go(wait=True)
rospy.sleep(5)
"""

"""
self.minRange = [-50, -20, -90, -80, -20, -90, 0]
self.maxRange = [ 50,  90,  20,  80,  80, 90, 0]
        """
joint_positions1 = [0,0,0,0,0,0]
group1.set_joint_value_target(joint_positions1)
group1.go(wait=True)
current_pos = group1.get_current_pose().pose.position
current_angle =  group1.get_current_joint_values()
print ("pos1: "+ str(current_pos))
print(".....................")
print current_angle
rospy.sleep(2)


joint_positions2 = [0, -1.57, 1.57, 0, -1.57, 0]
group1.set_joint_value_target(joint_positions2)
group1.go(wait=True)
current_pos = group1.get_current_pose().pose.position
current_angle =  group1.get_current_joint_values()
print ("pos2: "+ str(current_pos))
print(".....................")
print current_angle
rospy.sleep(2)

moveit_commander.roscpp_shutdown()

