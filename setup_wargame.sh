#!/bin/bash

#########################################
#          Pre-install checks
#########################################

# Warn the user about running this on their host machine
# (because it makes various invasive settings-changes, and runs a ton of vulnerable services)
echo -e "\x1b[31;1mDON'T RUN THIS ON YOUR REAL COMPUTER\x1b[0m"
echo "Are you running this inside a VM? (If you don't know what that means, don't run the script.)"
read -p "(yes/no)> "
if [ "$REPLY" != 'yes' ]; then
    exit
fi

if [ "$USER" != 'root' ]; then
    echo "ERROR: Script must be run using root!"
    exit
fi

echo -e "\x1b[32;1mProceeding with the installation.\x1b[0m"

#########################################
#     Per-Machine Install Variables
#########################################

# change these things
export PUBKEY=""
export REALUSER='gameadmin'
export HOSTNAME='warzone'
export LEVELS_DIR='/levels'
export SKEL_DIR='/etc/skel'
export SKEL_LINK_DIR='/etc/cfg'
export TOOLS_DIR='/tools'
export TOOLOWNER='toolman'

# leave as is
export VIMRC=$(echo $SKEL_LINK_DIR/.vimrc)
export SCREENRC=$(echo $SKEL_LINK_DIR/.screenrc)
export BASHRC=$(echo $SKEL_LINK_DIR/.bashrc)
export PROFILE=$(echo $SKEL_LINK_DIR/.profile)
export GDBINIT=$(echo $SKEL_LINK_DIR/.gdbinit)
export R2CONF=$(echo $SKEL_LINK_DIR/.radare2rc)

#########################################
#             Basic Setup
#########################################

# hush login motd
touch .hushlogin

# update and apt-get a ton of stuff
apt-get update
apt-get -y upgrade
apt-get -y install unattended-upgrades htop fonts-inconsolata git gdb gcc gcc-multilib g++ g++-multilib git ltrace linux-source openssh-server python-pip ipython python-dev vim guile-2.0 unzip socat libncurses5-dev texinfo
sudo dpkg-reconfigure -plow unattended-upgrades

# Create main user
useradd -m -s /bin/bash $REALUSER
adduser $REALUSER sudo

# install ssh key
HOME_DIR=$(eval echo ~$REALUSER)
sudo -u $REALUSER mkdir $HOME_DIR/.ssh
chmod 700 $HOME_DIR/.ssh
sudo -u $REALUSER echo $PUBKEY > $HOME_DIR/.ssh/authorized_keys
chmod 600 $HOME_DIR/.ssh/authorized_keys
chown $REALUSER:$REALUSER $HOME_DIR/.ssh/authorized_keys
restart ssh

# set perms
chmod 0700 $HOME_DIR

# set hostname
old_hostname=$(cat /etc/hostname)
hostname "$HOSTNAME"
cat /etc/hosts | sed s/"$old_hostname"/"$HOSTNAME"/ > /tmp/newhosts
mv /tmp/newhosts /etc/hosts
echo "$HOSTNAME" > /etc/hostname

#########################################
#    Configure Wargame Environment
#########################################

# hardening / wargamification

# restricting access mostly means make root accessible only, chmod 700 or s/t
chmod 700 `which dmesg`
chmod 700 `which fuser`
chmod 700 `which htop`
chmod 700 `which kill`
chmod 700 `which killall`
chmod 700 `which lsof`
chmod 700 `which pgrep`
chmod 700 `which pkill`
chmod 700 `which ps`
chmod 700 `which screen`
chmod 700 `which su`
chmod 700 `which tmux`
chmod 700 `which top`
chmod 700 `which ulimit`
chmod 700 `which users`
chmod 700 `which w`
chmod 700 `which wall`
chmod 700 `which who`
chmod 700 `which write`

# restrict access to /proc/maps/
sed -i 's/^exit 0$//' /etc/rc.local
echo -e 'mount -o remount,hidepid=2 /proc\n' >> /etc/rc.local
mount -o remount,hidepid=2 /proc
chmod 551 /proc

# make /tmp be not world readable, have sticky bits
chmod 1773 /tmp

# disable ssh'ing ? (not sure if possible, but these make it harder)
iptables -A OUTPUT -p tcp --dport 22 -j DROP
chmod 700 `which ssh`

# disable aslr
echo 0 | tee /proc/sys/kernel/randomize_va_space
echo 'kernel.randomize_va_space = 0' > /etc/sysctl.d/01-disable-aslr.conf

# resource management, stop forkbombs and filling the server (nproclimit)
# make group for wargame users
groupadd gameuser
echo -e '@gameuser\thard\tnproc\t500' >> /etc/security/limits.conf
echo -e '@gameuser\t-\tpriority\t15' >> /etc/security/limits.conf

# on-login banner
chmod -x /etc/update-motd.d/*
echo -e '#!/bin/sh\ncat /etc/banner' > /etc/update-motd.d/00-banner
chmod +x /etc/update-motd.d/00-banner
echo 'G1swOzMxbSAgICAgICAgX19fX19fX19fX19fX19fX19fX18uX19fICBfX19fX19fX19fX19fX19f
X19fX19fX19fX19fXyAgICAgICAgICAgICAgICANCiAgICAgICAgXF9fX19fXyAgIFxfX19fX18g
ICBcICAgfC8gICBfX19fXy9cXyAgIF9fX19fL1xfICAgX19fIFwgICAgICAgICAgICAgICANCiAg
ICAgICAgIHwgICAgICAgXy98ICAgICBfX18vICAgfFxfX19fXyAgXCAgfCAgICBfXylfIC8gICAg
XCAgXC8gICAgICAgICAgICAgICANCiAgICAgICAgIHwgICAgfCAgIFx8ICAgIHwgICB8ICAgfC8g
ICAgICAgIFwgfCAgICAgICAgXFwgICAgIFxfX19fICAgICAgICAgICAgICANCiAgICAgICAgIHxf
X19ffF8gIC98X19fX3wgICB8X19fL19fX19fX18gIC8vX19fX19fXyAgLyBcX19fX19fICAvICAg
ICAgICAgICAgICANCiAgICAgICAgICAgICAgICBcLyAgICAgICAgICAgICAgICAgICAgICBcLyAg
ICAgICAgIFwvICAgICAgICAgXC8gICAgICAgICAgICAgICANChtbMDszNm0gX18gICAgICBfXyAg
X19fX18gX19fX19fX19fX19fX19fX19fX19fX19fX19fXyAgICBfX19fX19fICBfX19fX19fX19f
Xw0KLyAgXCAgICAvICBcLyAgXyAgXFxfX19fX18gICBcX19fXyAgICAvXF9fX19fICBcICAgXCAg
ICAgIFwgXF8gICBfX19fXy8NClwgICBcL1wvICAgLyAgL19cICBcfCAgICAgICBfLyAvICAgICAv
ICAvICAgfCAgIFwgIC8gICB8ICAgXCB8ICAgIF9fKV8gDQogXCAgICAgICAgLyAgICB8ICAgIFwg
ICAgfCAgIFwvICAgICAvXyAvICAgIHwgICAgXC8gICAgfCAgICBcfCAgICAgICAgXA0KICBcX18v
XCAgL1xfX19ffF9fICAvX19fX3xfICAvX19fX19fXyBcXF9fX19fX18gIC9cX19fX3xfXyAgL19f
X19fX18gIC8NCiAgICAgICBcLyAgICAgICAgIFwvICAgICAgIFwvICAgICAgICBcLyAgICAgICAg
XC8gICAgICAgICBcLyAgICAgICAgXC8gDQoNChtbMG0gICAgICAgIC0tLS0tLS0tLS0tLS0tLS0t
LS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tICAgICAgICANCg0KICAgICAg
ICAgICAgICAgICAgICAgICBDaGFsbGVuZ2VzIGFyZSBpbiAvbGV2ZWxzICAgICAgICAgICAgICAg
ICAgICAgICAgDQogICAgICAgICAgICAgICAgICAgUGFzc3dvcmRzIGFyZSBpbiAvaG9tZS9sYWIq
Ly5wYXNzICAgICAgICAgICAgICAgICAgICANCiAgICAgICAgICAgIFlvdSBjYW4gY3JlYXRlIGZp
bGVzIG9yIHdvcmsgZGlyZWN0b3JpZXMgaW4gL3RtcCAgICAgICAgICAgIA0KICAgICAgICAgICAg
ICAgICAgICANCiAgICAgICAgIC0tLS0tLS0tLS0tLS0tLS0tWyAbWzA7OTJtY29udGFjdEBycGlz
LmVjG1swbSBdLS0tLS0tLS0tLS0tLS0tLS0gICAgICAgICAgDQoNCg==' | base64 -d > /etc/banner
rm /etc/legal

# disable crontab
touch /etc/cron.allow

#more I'm sure

#########################################
#           Install Tools
#########################################

# make tools owner
useradd -M -s /bin/false $TOOLOWNER

# make tools dir
mkdir $TOOLS_DIR
chmod 777 $TOOLS_DIR

source ./external_tools.sh
install_pip2s
install_gdb_peda
install_checksec
install_radare2
install_fixenv
install_shtest

# set perms
chown -R $TOOLOWNER:$TOOLOWNER $TOOLS_DIR/*
chmod 775 $TOOLS_DIR

#########################################
#       Create Skeleton User
#########################################

# this should populate the skel folder with symlinks. That way any user we make later on the
# server will auto copy these settings, and they will be in a single location for editing.
export SKEL=$SKEL_DIR
mkdir $SKEL_LINK_DIR

# setup vim config
touch $VIMRC
(echo syntax on \
; echo set tabstop=4 softtabstop=4 shiftwidth=4 \
; echo set expandtab ai number ruler \
; echo highlight Comment ctermfg=green \
; echo set viminfo=) >> $VIMRC
echo "[+] Configured VIM!"

# setup .bashrc
cp $SKEL_DIR/.bashrc $BASHRC
(echo -e "\n# Start user config" \
; echo "export TERM=screen-256color" \
; echo "export PS1='\[\033[01;31m\]\u\[\033[00;37m\]@\[\033[01;32m\]\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '" \
; echo "export ENV='/etc/profile'" \
; echo "alias grep='grep --color=auto'" \
; echo "alias ls='ls --color=auto -l'" \
; echo "alias checksec='checksec --file'" \
; echo "alias ropgadget='ROPgadget --binary'" \
; echo "alias gdb='gdb -q'") >> $BASHRC
echo "[+] Configured bash!"

# setup .profile
cp $SKEL_DIR/.profile $PROFILE
echo "[+] Configured profile!"

# setup .gdbinit
(echo -e "\nset disassembly-flavor intel" \
; echo "set detach-on-fork off" \
; echo "set follow-fork-mode child") >> $GDBINIT
echo "[+] Configured gdb!"

# setup radare2 config
echo 'e scr.utf8 = true' > $R2CONF
mkdir -p $SKEL_LINK_DIR/.config/radare2
ln -s /dev/null $SKEL_LINK_DIR/.config/radare2/history

# make sure the admin user gets these pretty confs, too
cp $SKEL_LINK_DIR/.* /home/$REALUSER/
chown -R $REALUSER:$REALUSER $(eval echo ~$REALUSER)

# start fresh and add symlinks
rm -rf $SKEL_DIR
mkdir $SKEL_DIR
ln -s $VIMRC $SKEL_DIR/.vimrc
ln -s $BASHRC $SKEL_DIR/.bashrc
ln -s $PROFILE $SKEL_DIR/.profile
ln -s $GDBINIT $SKEL_DIR/.gdbinit
ln -s $R2CONF $SKEL_DIR/.radare2rc
ln -s $SKEL_LINK_DIR/.config $SKEL_DIR/.config

# disable bash history
ln -s /dev/null $SKEL_DIR/.bash_history
chattr -fR +i $SKEL_LINK_DIR

#########################################
#             Setup wargame
#########################################

function setup_level {
  if [ "$#" -ne 7 ]; then
      echo "ERROR: Missing arguments"
      exit
  fi
  # rename arguments
  username=$1
  next_level=$2
  next_password=$3
  level_subdir=$4
  local level_files=("${!5}")
  local level_owners=("${!6}")
  local level_perms=("${!7}")

  # unchattr passwd
  chattr -f -i /etc/passwd
  chattr -f -i /etc/shadow

  # make current level user
  user_home=$(eval echo ~$username)
  id -u $username &> /dev/null; uexist=$?;
  if [ "$uexist" -eq "1" ]; then
      useradd -m -s /bin/bash -G gameuser $username
      user_home=$(eval echo ~$username)
      echo $username:$([ -f $user_home/.pass ] && cat $user_home/.pass \
                       || echo $level_subdir"start") | chpasswd
  fi
  # make next level user
  next_home=$(eval echo ~$next_level)
  id -u $next_level &> /dev/null; uexist=$?;
  if [ "$uexist" -eq "1" ]; then
      useradd -m -s /bin/bash -G gameuser $next_level
      next_home=$(eval echo ~$next_level)
      echo $next_level:$next_password | chpasswd
      echo $next_password > $next_home/.pass
      chown $next_level:$next_level $next_home/.pass
      chmod 0400 $next_home/.pass
  fi
  # make sure everything is unchattr'd
  chattr -fR -i $user_home
  chattr -fR -i $next_home
  chattr -fR -i $LEVELS_DIR

  # add the levels and perms
  llen=${#level_files[@]}
  for (( i=0; i<${llen}; i++ )); do
      chown ${level_owners[$i]} $LEVELS_DIR/$level_subdir/${level_files[$i]}
      chmod ${level_perms[$i]} $LEVELS_DIR/$level_subdir/${level_files[$i]}
  done

  # re-chattr levels/directories
  chattr -fR +i $user_home
  chattr -fR +i $next_home
  chattr -fR +i $LEVELS_DIR

  # re-chattr passwd
  chattr -f +i /etc/passwd
  chattr -f +i /etc/shadow
}

function add_simple_level {
    local level_files=("$1" "$1.c")
    local level_owners=("$2:$1" "$1:$1")
    local level_perms=("4550" "0400")
    setup_level $1 $2 $3 $4 level_files[@] level_owners[@] level_perms[@]
}

function add_socat_on_start {
    # $1 = working directory
    # $2 = exec cmd
    # $3 = listen part
    # $4 = user to run exec as
    echo -e "cd $1\nsocat TCP-LISTEN:$3,reuseaddr,fork,su=$4 EXEC:\"$2\" &" >> /etc/rc.local
}

# Stick levels folder where it belongs
mkdir $LEVELS_DIR
if [ -d "./levels" ]
then
    cp -R ./levels/* $LEVELS_DIR
else
    echo "ERROR: ./levels not found"
    exit
fi

# Add LICENSE and ACKNOWLEDGEMENTS
cp LICENSE $LEVELS_DIR/LICENSE
cp LICENSE $LEVELS_DIR/CHANGELOG
cp ACKNOWLEDGEMENTS $LEVELS_DIR/ACKNOWLEDGEMENTS
chmod 444 $LEVELS_DIR/ACKNOWLEDGEMENTS
chmod 444 $LEVELS_DIR/CHANGELOG
chmod 444 $LEVELS_DIR/LICENSE

# Add lab01
# Will throw some errors since no source file, but w/e
lab=lab1
add_simple_level $lab'C' $lab'B' 'n0_str1ngs_n0_pr0bl3m' lab01
add_simple_level $lab'B' $lab'A' '1337_3nCRyptI0n_br0' lab01
add_simple_level $lab'A' $lab'end' '1uCKy_Gue55' lab01

# Add lab02
lab=lab2
add_simple_level $lab'C' $lab'B' '1m_all_ab0ut_d4t_b33f' lab02
add_simple_level $lab'B' $lab'A' 'i_c4ll_wh4t_i_w4nt_n00b' lab02
add_simple_level $lab'A' $lab'end' 'D1d_y0u_enj0y_y0ur_cats?' lab02

# Add lab03
lab=lab3
add_simple_level $lab'C' $lab'B' 'th3r3_iz_n0_4dm1ns_0n1y_U!' lab03
add_simple_level $lab'B' $lab'A' 'wh0_n33ds_5h3ll3_wh3n_U_h4z_s4nd' lab03
add_simple_level $lab'A' $lab'end' 'sw00g1ty_sw4p_h0w_ab0ut_d3m_h0ps' lab03

# Add lab04
lab=lab4
add_simple_level $lab'C' $lab'B' 'bu7_1t_w4sn7_brUt3_f0rc34b1e!' lab04
add_simple_level $lab'B' $lab'A' 'fg3ts_d0e5n7_m4k3_y0u_1nv1nc1bl3' lab04
add_simple_level $lab'A' $lab'end' '1t_w4s_ju5t_4_w4rn1ng' lab04

# Add lab05
lab=lab5
add_simple_level $lab'C' $lab'B' 's0m3tim3s_r3t2libC_1s_3n0ugh' lab05
add_simple_level $lab'B' $lab'A' 'th4ts_th3_r0p_i_lik3_2_s33' lab05
add_simple_level $lab'A' $lab'end' 'byp4ss1ng_d3p_1s_c00l_am1rite' lab05

# Add lab06
lab=lab6
add_simple_level $lab'C' $lab'B' 'p4rti4l_0verwr1tes_r_3nuff' lab06
level_files=($lab'B' $lab'B.c' $lab'B.readme')
level_owners=($lab'A:'$lab'B' $lab'B:'$lab'B' $lab'B:'$lab'B')
level_perms=('0550' '0400' '0400')
setup_level $lab'B' $lab'A' 'strncpy_1s_n0t_s0_s4f3_l0l' lab06 level_files[@] level_owners[@] level_perms[@]
add_socat_on_start "$LEVELS_DIR/lab06" "timeout 300 $LEVELS_DIR/lab06/lab6B" 6642 $lab'A'
add_simple_level $lab'A' $lab'end' 'eye_gu3ss_0n_@ll_mah_h0m3w3rk' lab06

# Add lab07
lab=lab7
add_simple_level $lab'C' $lab'A' 'us3_4ft3r_fr33s_4re_s1ck' lab07
level_files=($lab'A' $lab'A.c' $lab'A.readme')
level_owners=($lab'end:'$lab'A' $lab'A:'$lab'A' $lab'A:'$lab'A')
level_perms=('0550' '0400' '0400')
setup_level $lab'A' $lab'end' '0verfl0wz_0n_th3_h3ap_4int_s0_bad' lab07 level_files[@] level_owners[@] level_perms[@]
add_socat_on_start "$LEVELS_DIR/lab07" "timeout 60 $LEVELS_DIR/lab07/lab7A" 7741 $lab'end'

# Add lab08
lab=lab8
add_simple_level $lab'C' $lab'B' '3v3ryth1ng_Is_@_F1l3' lab08
add_simple_level $lab'B' $lab'A' 'Th@t_w@5_my_f@v0r1t3_ch@11' lab08
level_files=($lab'A' $lab'A.c' $lab'A.readme')
level_owners=($lab'end:'$lab'A' $lab'A:'$lab'A' $lab'A:'$lab'A')
level_perms=('0550' '0400' '0400')
setup_level $lab'A' $lab'end' 'H4x0r5_d0nt_N33d_m3t4pHYS1c5' lab08 level_files[@] level_owners[@] level_perms[@]
add_socat_on_start "$LEVELS_DIR/lab08" "timeout 60 $LEVELS_DIR/lab08/lab8A" 8841 $lab'end'

# Add lab09 (cpp and networked)
lab=lab9
level_files=($lab'C' $lab'C.cpp' $lab'C.readme')
level_owners=($lab'A:'$lab'C' $lab'C:'$lab'C' $lab'C:'$lab'C')
level_perms=('0550' '0400' '0400')
setup_level $lab'C' $lab'A' '1_th0uGht_th4t_w4rn1ng_wa5_l4m3' lab09 level_files[@] level_owners[@] level_perms[@]
add_socat_on_start "$LEVELS_DIR/lab09" "timeout 60 $LEVELS_DIR/lab09/lab9C" 9943 $lab'A'
level_files=($lab'A' $lab'A.cpp' $lab'A.readme')
level_owners=($lab'end:'$lab'A' $lab'A:'$lab'A' $lab'A:'$lab'A')
level_perms=('0550' '0400' '0400')
setup_level $lab'A' $lab'end' '1_d1dNt_3v3n_n33d_4_Hilti_DD350' lab09 level_files[@] level_owners[@] level_perms[@]
add_socat_on_start "$LEVELS_DIR/lab09" "timeout 300 $LEVELS_DIR/lab09/lab9A" 9941 $lab'end'

# Add project1
lab=project1
level_files=('tw33tchainz' 'README')
level_owners=($lab'_priv:'$lab $lab':'$lab)
level_perms=('4550' '0400')
setup_level $lab $lab'_priv' 'm0_tw33ts_m0_ch4inz_n0_m0n3y' $lab level_files[@] level_owners[@] level_perms[@]

# Add project2
lab=project2
level_files=('rpisec_nuke' 'README' 'GENERAL_CROWELL.key' 'GENERAL_DOOM.key' 'GENERAL_HOTZ.key')
level_owners=($lab'_priv:'$lab $lab':'$lab $lab'_priv:'$lab $lab'_priv:'$lab $lab'_priv:'$lab)
level_perms=('0550' '0400' '0400' '0400' '0400')
setup_level $lab $lab'_priv' 'th3_pr1nt_funct10n_w4s_100_l!n3s_al0ne' $lab level_files[@] level_owners[@] level_perms[@]
add_socat_on_start "$LEVELS_DIR/project2" "timeout 300 $LEVELS_DIR/project2/rpisec_nuke" 31337 $lab'_priv'

# Add lecture examples
lecuser=lecture
lecpriv=lecture_priv
## Make users
chattr -fR -i /etc/passwd
chattr -fR -i /etc/shadow
useradd -m -s /bin/bash -G gameuser $lecuser
echo $lecuser':'$lecuser | chpasswd
useradd -m -s /bin/bash -G gameuser $lecpriv
passwd -l $lecpriv
chattr -fR +i $(eval echo ~$lecuser)
chattr -fR +i $(eval echo ~$lecpriv)
chattr -fR +i /etc/passwd
chattr -fR +i /etc/shadow
## Set permissions
chattr -fR -i $LEVELS_DIR
find /levels/lecture -type f | xargs -I {} chown $lecpriv:$lecuser {} {}
find /levels/lecture -type f | xargs -I {} chmod 4550 {} {}
find /levels/lecture -type f -name '*.c*' | xargs -I {} chown $lecuser:$lecuser {} {}
find /levels/lecture -type f -name '*.c*' | xargs -I {} chmod 0400 {} {}
chattr -fR +i $LEVELS_DIR

# This needs to be here
echo 'exit 0' >> /etc/rc.local

echo '*** DONE! ***'
echo -n 'reboot now? (y/n): '
read REBOOT
if [ "$REBOOT" == 'y' ]; then
    reboot
else
    echo 'You must reboot for certain settings to kick in'
    echo 'Please reboot soon'
fi
