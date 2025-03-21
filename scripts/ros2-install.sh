#! /bin/bash

# check for root
if [[ "$(whoami)" != "root" ]]; then
   echo "Script must be run as root or using sudo"
   exit 1
fi

# Check for correct Ubuntu version
VERSION="$(lsb_release -c | cut -f 2)"

if [[ "$VERSION" != "jammy" ]]; then
   echo ""
   echo "Wrong Operating System - need Ubuntu 22.04"
   exit 1
fi

echo "Updating package library"

apt-get update -y

# I was going to sneak vim in there but you beat me to it :)
echo "Installing helper programs"
apt-get install curl git vim make cmake g++ clang++ ssh htop -y

echo "Setting correct locale"
apt install locales -y
locale-gen en_US en_US.UTF-8
update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

echo "Adding ROS2 apt repository"
apt install software-properties-common -y
add-apt-repository universe

echo "Adding ROS2 GPG key"
curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

echo "Installing development tools"
apt update -y && apt install ros-dev-tools -y
apt update -y
apt upgrade -y
apt install ros-iron-desktop -y
apt install ros-iron-ros-base -y
source /opt/ros/iron/setup.bash
echo "source /opt/ros/iron/setup.bash" >> /home/$SUDO_USER/.bashrc

apt update -y
apt upgrade -y

echo "ROS2 Iron Succesfully installed"
echo "See https://docs.ros.org/en/iron/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Nodes/Understanding-ROS2-Nodes.html"
echo "    https://docs.ros.org/en/iron/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Topics/Understanding-ROS2-Topics.html"
echo "to start learning about ROS2"
echo ""
echo "Open new terminal to see ros2 command"
