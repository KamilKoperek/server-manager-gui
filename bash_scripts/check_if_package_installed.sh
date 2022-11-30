echo -n $(dpkg-query -W -f='${Status}' $1 2>/dev/null | grep -c "ok installed")
