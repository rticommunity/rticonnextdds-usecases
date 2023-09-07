##### Mofidy these variables if you need to use that specific profile
##### Run with $ source qos_variables.sh

##### For LAN, LAN_NoIpFrag and WAN_Active. This avois sending / receiving duplicate traffic in most cases
export ALLOW_INTERFACES_LIST=10.30.2.143

##### For WAN_Active
# WAN_INITIAL_PEER can have 0@udpv4_wan://10.10.10.10:7400 format or rtps@udpv4_wan://10.10.10.10:7400 for CDS
export WAN_INITIAL_PEER=0@udpv4_wan://pmdemo.rti.com:8600

##### For WAN_PASSIVE
# PUBLIC_ADDRESS can have the 10.10.10.10 format
export PUBLIC_ADDRESS=10.10.10.10
export PUBLIC_PORT=0
export INTERNAL_PORT=0