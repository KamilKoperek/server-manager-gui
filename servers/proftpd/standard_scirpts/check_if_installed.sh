if dpkg-query -W -f'${Status}' "$pkg" 2>/dev/null | grep -q "ok installed";
then
echo 1
else
echo 0
fi
