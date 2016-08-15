#! /bin/bash


Main(){
	inp1=0
	inp2=0
	inp3=0
	idx=0
	count=0
	echo "                                Database" >output.txt
	divider=======================================
	divider=$divider$divider
	declare -a info_arr
	header="\n %-15s %15s %15s %15s\n"
	format=" %-15s %15s %15s %15s\n"

	width=70
	while ! [ $inp1 == "h" ]
	do
		flag="no"
		echo ''
		echo "Welcome to the contact database, please select from the following menu:" 
		echo "(a)Find a record"
		echo "(b)Add a new record"
		echo "(c)Update a record"
		echo "(d)Remove a record"
		echo "(e)View all records"
		echo "(f)Import existing database"
		echo "(g)Alphabetize records"
		echo "(h)Quit"
		read -p "> " inp1
		echo "You entered: "$inp1

		if [ $inp1 = "a" ]
		then
			Search 
		fi

		if [ $inp1 = "b" ]
		then
			Add
		fi

		if [ $inp1 = "c" ]
		then
			Update 
		fi

		if [ $inp1 = "d" ]
		then
			Remove 
		fi

		if [ $inp1 = "e" ]
		then
			View 
		fi	

		if [ $inp1 = "f" ]
		then
			Import
		fi
        
		if [ $inp1 = "g" ]
		then 
		        Alphabetize
	        fi 
		
		if [ $inp1 = "h" ]
		then
			Closing 
		fi

done


}

Search(){
	echo "Press 1 to search by Name"
	echo "Press 2 to search by Address"
	echo "Press 3 to search by Phone Number"
	echo "Press 4 to search by Email"
	read -p "> " inp2
	if [ $inp2 = "1" ]
	then
		echo "Enter the name you want to search"
		read -p ">" inp3
		for ((i=0;i<count;i++))do
			if [ "$inp3" = "${info_arr[(4*i)+0]}" ]
			then
				echo "Search found"
				printf "$header" "NAME" "Address" "Number" "Email"
				printf "%$width.${width}s\n" "$divider"
				printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
				flag="y"
			fi
		done
		if [ "$flag" != "y" ]
		then
			echo "No results found"
		fi
	fi

	if [ $inp2 = "2" ]
	then
		echo "Enter the address you want to search"
		read -p ">" inp3
		for ((i=0;i<count;i++))do
			if [ "$inp3" = "${info_arr[(4*i)+1]}" ]
			then
				echo "Search found"
				printf "$header" "NAME" "Address" "Number" "Email"
				printf "%$width.${width}s\n" "$divider"
				printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
				flag="y"
			fi
		done
		if [ "$flag" != "y" ]
		then
			echo "No results found"
		fi
	fi

	if [ $inp2 = "3" ]
	then
		echo "Enter the phone number you want to search(###-###-####)"
		read -p ">" inp3
		for ((i=0;i<count;i++))do
			if [ "$inp3" = "${info_arr[(4*i)+2]}" ]
			then
				echo "Search found"
				printf "$header" "NAME" "Address" "Number" "Email"
				printf "%$width.${width}s\n" "$divider"
				printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
				flag="y"
			fi
		done
		if [ "$flag" != "y" ]
		then
			echo "No results found"
		fi
	fi

	if [ $inp2 = "4" ]
	then
		echo "Enter the email you want to search"
		read -p ">" inp3
		for ((i=0;i<count;i++))do
			if [ "$inp3" = "${info_arr[(4*i)+3]}" ]
			then
				echo "Search found"
				printf "$header" "NAME" "Address" "Number" "Email"
				printf "%$width.${width}s\n" "$divider"
				printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
				flag="y"
			fi
		done
		if [ "$flag" != "y" ]
		then
			echo "No results found"
		fi
	fi
}

Add(){
	echo "Enter name:"
	read -p "> " name1
	echo "Enter address:"
	read -p "> " addr1
	echo "Enter phone number(###-###-####):"
	read -p "> " pnum1
	echo "Enter email:"
	read -p "> " email1

	info_arr[(4*count)+0]=$name1
	info_arr[(4*count)+1]=$addr1
	info_arr[(4*count)+2]=$pnum1
	info_arr[(4*count)+3]=$email1

	count=$((count+1))
}

Update(){
	echo "Updating a record, search for record to update"
	echo "Press 1 to search by Name"
	echo "Press 2 to search by Address"
	echo "Press 3 to search by Phone Number"
	echo "Press 4 to search by Email"
	read -p "> " inp2

	if [ $inp2 = "1" ]
	then
		echo "Enter the name you want to search"
		read -p ">" inp3
		for ((i=0;i<count;i++))do
			if [ "$inp3" = "${info_arr[(4*i)+0]}" ]
			then
				echo "Search found"
				printf "$header" "NAME" "Address" "Number" "Email"
				printf "%$width.${width}s\n" "$divider"
				printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
				idx=$i
				flag="y"
			fi
		done
		if [ "$flag" != "y" ]
		then
			echo "No results found"
		fi
		fi

		if [ $inp2 = "2" ]
		then
			echo "Enter the address you want to search"
			read -p ">" inp3
			for ((i=0;i<count;i++))do
				if [ "$inp3" = "${info_arr[(4*i)+1]}" ]
				then
					echo "Search found"
					printf "$header" "NAME" "Address" "Number" "Email"
					printf "%$width.${width}s\n" "$divider"
					printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
					idx=$i
					flag="y"
				fi
			done
			if [ "$flag" != "y" ]
			then
				echo "No results found"
			fi
		fi

		if [ $inp2 = "3" ]
		then
			echo "Enter the phone number you want to search(###-###-####)"
			read -p ">" inp3
			for ((i=0;i<count;i++))do
				if [ "$inp3" = "${info_arr[(4*i)+2]}" ]
				then
					echo "Search found"
					printf "$header" "NAME" "Address" "Number" "Email"
					printf "%$width.${width}s\n" "$divider"
					printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
					idx=$i
					flag="y"
				fi
			done
			if [ "$flag" != "y" ]
			then
				echo "No results found"
			fi
		fi

		if [ $inp2 = "4" ]
		then
			echo "Enter the email you want to search"
			read -p ">" inp3
			for ((i=0;i<count;i++))do
				if [ "$inp3" = "${info_arr[(4*i)+3]}" ]
				then
					echo "Search found"
					printf "$header" "NAME" "Address" "Number" "Email"
					printf "%$width.${width}s\n" "$divider"
					printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
					idx=$i
					flag="y"

				fi
			done
			if [ "$flag" != "y" ]
			then
				echo "No results found"
			fi
		fi

		echo "Press 1 to update Name"
		echo "Press 2 to update Address"
		echo "Press 3 to update Phone Number"
		echo "Press 4 to update Email"
		read -p ">" inp2

		if [ $inp2 = "1" ]
		then
			echo "Enter name:"
			read -p ">" inp3
			info_arr[(4*idx)+0]=$inp3
		fi

		if [ $inp2 = "2" ]
		then
			echo "Enter address:"
			read -p ">" inp3
			info_arr[(4*idx)+1]=$inp3
		fi

		if [ $inp2 = "3" ]
		then
			echo "Enter phone number(###-###-####):"
			read -p ">" inp3
			info_arr[(4*idx)+2]=$inp3
		fi

		if [ $inp2 = "4" ]
		then
			echo "Enter email:"
			read -p ">" inp3
			info_arr[(4*idx)+3]=$inp3
		fi
}

Remove(){
	echo "Removing a record, search for record to update"
		echo "Press 1 to search by Name"
		echo "Press 2 to search by Address"
		echo "Press 3 to search by Phone Number"
		echo "Press 4 to search by Email"
		read -p "> " inp2

		if [ $inp2 = "1" ]
		then
			echo "Enter the name you want to search"
			read -p ">" inp3
			for ((i=0;i<count;i++))do
				if [ "$inp3" = "${info_arr[(4*i)+0]}" ]
				then
					echo "Search found"
					printf "$header" "NAME" "Address" "Number" "Email"
					printf "%$width.${width}s\n" "$divider"
					printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
					idx=$i
					flag="y"
				fi
			done
			if [ "$flag" != "y" ]
			then
				echo "No results found"
			fi
		fi

		if [ $inp2 = "2" ]
		then
			echo "Enter the address you want to search"
			read -p ">" inp3
			for ((i=0;i<count;i++))do
				if [ "$inp3" = "${info_arr[(4*i)+1]}" ]
				then
					echo "Search found"
					printf "$header" "NAME" "Address" "Number" "Email"
					printf "%$width.${width}s\n" "$divider"
					printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
					idx=$i
					flag="y"
				fi
			done
			if [ "$flag" != "y" ]
			then
				echo "No results found"
			fi
		fi

		if [ $inp2 = "3" ]
		then
			echo "Enter the phone number you want to search(###-###-####)"
			read -p ">" inp3
			for ((i=0;i<count;i++))do
				if [ "$inp3" = "${info_arr[(4*i)+2]}" ]
				then
					echo "Search found"
					printf "$header" "NAME" "Address" "Number" "Email"
					printf "%$width.${width}s\n" "$divider"
					printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
					idx=$i
					flag="y"
				fi
			done
			if [ "$flag" != "y" ]
			then
				echo "No results found"
			fi
		fi

		if [ $inp2 = "4" ]
		then
			echo "Enter the email you want to search"
			read -p ">" inp3
			for ((i=0;i<count;i++))do
				if [ "$inp3" = "${info_arr[(4*i)+3]}" ]
				then
					echo "Search found"
					printf "$header" "NAME" "Address" "Number" "Email"
					printf "%$width.${width}s\n" "$divider"
					printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" 
					idx=$i
					flag="y"
				fi
			done
			if [ "$flag" != "y" ]
			then
				echo "No results found"
			fi
		fi

		echo "Press 1 to delete record"
		read -p ">" inp3
		if [ $inp3 = "1" ]
		then
			for ((i=idx;i<count;i++))do	
					x=$((i+1))
					info_arr[(4*i)+0]="${info_arr[(4*x)+0]}"
					info_arr[(4*i)+1]="${info_arr[(4*x)+1]}"
					info_arr[(4*i)+2]="${info_arr[(4*x)+2]}"
					info_arr[(4*i)+3]="${info_arr[(4*x)+3]}"
				
			done
			echo "Record deleted"
		else
			echo "Record not deleted"f
		fi
		
		count=$((count-1))
}

View(){
	echo "Press 1 to view all entries in the database"
	echo "Press 2 to view names & address"
	echo "Press 3 to view names & phone numbers"
	echo "Press 4 to view names & emails"
	read -p "> " inp2

	if [ $inp2 = "1" ]
		then
			printf "$header" "NAME" "Address" "Number" "Email"
			printf "%$width.${width}s\n" "$divider"
			for ((i=0;i<count;i++))do
				printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}"
			done
		fi

	if [ $inp2 = "2" ]
		then
			printf "$header" "NAME" "Address"
			printf "%$width.${width}s\n" "$divider"
			for ((i=0;i<count;i++))do
				printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}"
			done
		fi

	if [ $inp2 = "3" ]
		then
			printf "$header" "NAME" "Number"
			printf "%$width.${width}s\n" "$divider"
			for ((i=0;i<count;i++))do
				printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+2]}"
			done
		fi

	if [ $inp2 = "4" ]
		then
			printf "$header" "NAME" "Email"
			printf "%$width.${width}s\n" "$divider"
			for ((i=0;i<count;i++))do
				printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+3]}"
			done
		fi
}

Closing(){
	echo "Exiting program"
		printf "$header" "NAME" "Address" "Number" "Email" >>output.txt
		printf "%$width.${width}s\n" "$divider" >>output.txt
		for ((i=0;i<count;i++))do
			printf "$format" "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}" >>output.txt
		done
		exit 0
}

Import(){
	echo "Importing Database"
	echo "Please enter file to read pre existing database"
	read -p ">" inp1

	if [ -f "$inp1" ]
	then
		echo "file found and opened."
	else
		echo "file not found."

	fi

	echo "Press 1 to merge with current databases"
	echo "Press 2 to override current database"
	read -p ">" inp2

	if [ "$inp2" = "1" ]
	then
		while read line
    	do
        	name1=`echo $line | cut -d, -f1`
        	addr1=`echo $line | cut -d, -f2`
        	pnum1=`echo $line | cut -d, -f3`
        	email1=`echo $line | cut -d, -f4`

        	info_arr[(4*count)+0]=$name1
			info_arr[(4*count)+1]=$addr1
			info_arr[(4*count)+2]=$pnum1
			info_arr[(4*count)+3]=$email1

			count=$((count+1))
    	done<$inp1
	fi


	if [ "$inp2" = "2" ]
	then
		count=0
		while read line
    	do
        	name1=`echo $line | cut -d, -f1`
        	addr1=`echo $line | cut -d, -f2`
        	pnum1=`echo $line | cut -d, -f3`
        	email1=`echo $line | cut -d, -f4`

        	info_arr[(4*count)+0]=$name1
			info_arr[(4*count)+1]=$addr1
			info_arr[(4*count)+2]=$pnum1
			info_arr[(4*count)+3]=$email1

			count=$((count+1))
    	done<$inp1
	fi
}

Alphabetize(){
	     echo "Database Alphabetized"
	     printf "$header" "NAME" "Address" "Number" "Email"
	     printf "%$width.${width}s\n" "$divider"
             for ((i=0;i<count;i++))
             do
                 ARRAY[i]=$(printf '%-15s %15s %15s %15s\n' "${info_arr[(4*i)+0]}" "${info_arr[(4*i)+1]}" "${info_arr[(4*i)+2]}" "${info_arr[(4*i)+3]}")
	     done

	     for el in "${ARRAY[@]}"
             do
                 echo "$el"
             done | sort
             
}

Main
