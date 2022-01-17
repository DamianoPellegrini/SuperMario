if [[ $1 == "Release" ]]; then
	echo "Running in Release mode"
	config="Release"
else
	echo "Running in Debug mode"
	config="Debug"
fi

appName="SuperMario"
if [[ $OSTYPE == "darwin"* ]]; then
	appName="SuperMario.app"
fi
echo $appName

(cd ./bin/$config && "./$appName")
