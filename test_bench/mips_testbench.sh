srcPath="./test_bench/tests"
simPath=$1
warnings=()
failures=()

# Check if simulator argument was passed
if [ "$simPath" == "" ]
then
  echo "Critical: Expected a simulator as an input"
  exit 1
fi

# For every binary file test
for inputBin in $srcPath/*.bin
do 

  # Load meta file data
  metaFile="${inputBin%.*}.meta"
  metaData=()
  while read -r line  || [[ -n "$line" ]]; do
      metaData+=("${line//#}")
  done < "$metaFile"

  # Get test ID
  testID=$(basename "$inputBin")
  testID="${testID%%.*}"
  testID=${testID// /-}

  # Load attributes from meta file for the output text
  instruction=${metaData[0]}
  expectedReturn=${metaData[1]}
  author=${metaData[2]}
  description=${metaData[3]}
  input=${metaData[4]}
  expectedOutput=${metaData[5]}
  
  # Run depending on the input empty or not
  if [ -f "$input" ]
  then
    simOutput=$(cat "$input" | "$simPath" "$inputBin")
  else
    simOutput=$(echo "$input" | "$simPath" "$inputBin")
  fi

  # Get simulator output
  simReturn=$?

  # Convert to signed 8 bits number
  if [ $simReturn -ge 128 ]
  then
    ((return-=256))
  fi

  status="PASS"

  # Output text form: "TestId , Instruction , Status , Author [, Message]"
  message=""

  # Is there a description?
  if [ ! "$description" = "" ]
  then
    message="$description "
  fi

  # Is the return incorrect?
  if [ ! "$simReturn" = "$expectedReturn" ]
  then
    status="FAIL"
    message+=" (return failure: expected $expectedReturn but received $simReturn)"
  fi

  if [ ! "$simOutput" = "$expectedOutput" ]
  then
    status="FAIL"
    message+=" (output failure: expected $expectedOutput but received $simOutput)"
  fi

  echo "$testID, $instruction, $status, $author, $message"

  

done