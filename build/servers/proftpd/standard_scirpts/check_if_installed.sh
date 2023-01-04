if dpkg-query -W -f'${Status}' "proftpd-basic" 2>/dev/null | grep -q "ok installed";
then
echo 1
else
echo 0
fi
