#!/bin/sh

#
# Original version from the OpenWrt project.
#

# Interfaces
LAN=eth0

## CLEAR TABLES
iptables -t filter -F
iptables -t filter -X

### INPUT
###  (connections with the router as destination)

  # base case
  iptables -P INPUT DROP
  iptables -A INPUT -m state --state INVALID -j DROP
  iptables -A INPUT -m state --state RELATED,ESTABLISHED -j ACCEPT
  iptables -A INPUT -p tcp --tcp-flags SYN SYN --tcp-option \! 2 -j  DROP

  # allow
  iptables -A INPUT -p icmp -j ACCEPT                           # allow ICMP
  iptables -A INPUT -p tcp --sport 22 -j ACCEPT                 # allow SSH
  iptables -A INPUT -p tcp --sport 80 -j ACCEPT                 # allow HTTP
  iptables -A INPUT -p tcp --sport 443 -j ACCEPT                # allow HTTPS

  # reject (what to do with anything not allowed earlier)
  iptables -A INPUT -p tcp -j REJECT --reject-with tcp-reset
  iptables -A INPUT -j REJECT --reject-with icmp-port-unreachable

### OUTPUT
### (connections with the router as source)

  # base case
  iptables -P OUTPUT DROP
  iptables -A OUTPUT -m state --state INVALID -j DROP
  iptables -A OUTPUT -m state --state RELATED,ESTABLISHED -j ACCEPT

  #
  # insert accept rule here
  #

  # allow
  iptables -A OUTPUT -j ACCEPT          #allow everything out

  # reject (what to do with anything not allowed earlier)
  iptables -A OUTPUT -p tcp -j REJECT --reject-with tcp-reset
  iptables -A OUTPUT -j REJECT --reject-with icmp-port-unreachable

