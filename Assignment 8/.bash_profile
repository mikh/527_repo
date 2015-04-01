# .bash_profile

# Copy this to ~/.bash_profile if you don't already have a .bash_profile.
# If you do, make sure to add the "source /ad/eng/software..."

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# User specific environment and startup programs

source /mnt/nokrb/sge/bu-eng/common/settings.sh
source /afs/bu.edu/x86_bulnx50/IT/Intel/bin/intel64/iccvars_intel64.sh
PATH=$PATH:$HOME/bin

export PATH
unset USERNAME
