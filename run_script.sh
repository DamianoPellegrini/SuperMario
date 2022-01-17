appName="SuperMario"
if [[ $OSTYPE == "darwin"* ]]; then
	appName="SuperMario.app"
fi
echo $appName

(cd ./bin/Debug && ./$appName)
