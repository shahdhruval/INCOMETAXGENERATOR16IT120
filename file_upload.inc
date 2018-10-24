<?php
include('class.pdf2text.php');
function file_upload_callback($form , &$form_state) {
	$form['upload_item'] = array(
		'#type' => 'file',
		'#title' => 'Upload File'
	);
	
	if(isset($_SESSION['uploaded_link'])) {
		$form['uploaded_link'] = array(
			'#type' => 'markup',
			'#markup' => '<a href="' .$_SESSION['uploaded_link'] . '">' . $_SESSION['uploaded_link'] . '</a>'
		);
	}
	
	$form['upload_submit'] = array(
		'#type' => 'submit',
		'#value' => 'Upload File',
		'#submit' => array('upload_file_submit_callback')
	);
	
	return $form;
}

function upload_file_submit_callback($form, &$form_state){
	
	$validators = array(
		'file_validate_size' => array("2097152"),
		'file_validate_extensions' => array("pdf")
	);
	
	$location1 = 'public://';
	$uploadCheck = file_save_upload('upload_item', $validators, $location1);
	
	if($uploadCheck) {
		$link = file_create_url($uploadCheck->uri);
		$_SESSION['uploaded_link'] = $link; 
		
		$filepath = drupal_realpath($uploadCheck->uri);
		$a = new PDF2Text();
		$a->setFilename($filepath); 
		$a->decodePDF();
		$ans = $a->output(); 

		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Basic Salary=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+14,$end-$offset+2);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$income=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Conveyance Allowance=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+22,$end-$offset-2);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$extra_income = (int)$out;
		$total_sal=$income+$extra_income; 
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Professional Tax=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+18,$end-$offset-6);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$professional_tax =(int)$out;
		$mediclaim = 0;
		$jmp;$jump;

		//$total_sal=0;
		$gross_salary;
		$full_total;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Insurance Premium=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+18,$end-$offset-3);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$insurance_premium=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Child tution fees=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+18,$end-$offset);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$child_tution_fees=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"House Loan Interest=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+20,$end-$offset+1);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$house_loan_interest=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Educational Loan Interest=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+27,$end-$offset-5);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$educational_loan_interest=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Mediclaim=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+10,$end-$offset-9);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$mediclaim=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"PF=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+3,$end-$offset-1);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$provident_fund=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Mutual Fund=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+10,$end-$offset+5);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$mutual_fund=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Insurance Prepaid=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+19,$end-$offset-3);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$insurance_pre_paid=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Public Provident Fund=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+22,$end-$offset+1);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$public_provident_fund=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"National saving certificate=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+29,$end-$offset-1);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$national_saving_certificate=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"United Link Insurance=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+23,$end-$offset);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$united_link_insurance=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"Housing Loan=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+14,$end-$offset+1);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$sd=40000;
		$tax_income;
		$cess=0; 
		$final_tax=0; $final_tax1=0; 
		$total_salr=0;
		$housing_loan=(int)$out;
		$out = '';
		$offset = 0;
		while ( $offset = strpos($ans,"NPS=",$offset) )
		{
		  $end = strpos($ans,' ',$offset);
		  if ( $end )
		    $out .= substr($ans,$offset+20,$end-$offset+1);
		  else
		    $out .= substr($ans,$offset);

		  $offset++;		
		}
		$nps=(int)$out;
		$tmp_1;
		$tmp_2; 
		$tmp_3; 
		$tmp_4; 
		$nps;
		$sd=40000;
		$ans1;
		if($total_sal<=250000) 
        {
            $tax_income=0;
            $final_tax= 0;
            
        }
        else if($total_sal>250000&&$total_sal<=500000) 
        {

            if($total_sal<=350000)
            {
                $total_sal=$total_sal-2500;
                /*tmp_1=total_sal-250000;
                ans1=tmp_1*(0.05f);
                ans1=ans-2500;
                if(ans1<=0){
                    final_tax=0;
                }
                else {
                    cess=ans1*(0.04f);
                    tax_income=ans1+cess;
                    final_tax=ans1+cess+stcg_tax+ltcg_tax;
                }*/
            }
            $tmp_1 = $total_sal - 250000;
            $ans = $tmp_1*(0.05);
            $cess = $ans1*(0.04);
            $tax_income=$ans1+$cess;
            $final_tax=$ans1+$cess;
        }
        else if($total_sal>500000&&$total_sal<=1000000)
        {
            $tmp_1=$total_sal-250000;
            $tmp_2=$tmp_1-250000;
            $tmp_3=$tmp_2*(0.20);
            $tmp_1=$tmp_1-$tmp_2;
            $tmp_2=$tmp_1*(0.05);
            $ans1=$tmp_3+$tmp_2;
            $cess=$ans1*(0.04);
            $tax_income=$ans1+$cess;
            $final_tax=$ans1+$cess;
        }
        else if($total_sal>1000000)
        {
            $tmp_1=$total_sal-250000;
            $tmp_2=$tmp_1-250000;
            $tmp_3=$tmp_2-500000;
            $tmp_4=$tmp_3;
            $tmp_3=$tmp_3*(0.3);
            $tmp_2=$tmp_2-$tmp_4;
            $tmp_2=$tmp_2*(0.2);
            $ans=$tmp_2+$tmp_3+12500;
            $cess=$ans1*(0.04);
            $tax_income=$ans1+$cess;
            $final_tax=$ans1+$cess;
        }
		if($professional_tax<=2400)
        {
            $total_salr = $total_sal - $professional_tax ;
        }
        else
        {
            $total_salr=$total_sal-2400;
        }
        if($house_loan_interest<=50000)//slab for the house loan interest is changed from 200000 to 50000 (SECTION 80D)
        {
             $total_salr=$total_salr-$house_loan_interest;
        }
        else
        {
            $total_salr=$total_salr-50000;
        }
        $total_salr=$total_salr-$educational_loan_interest;
        if($mediclaim<=50000)//slab for the mediclaim is changed from 25000 to 50000 (SECTION 80D)
        {
            $total_salr=$total_salr-$mediclaim;
        }
        else
        {
            $total_salr=$total_salr-50000;
        }

        $temp_final_ded;
        $temp_final_ded=$provident_fund+$insurance_premium+$child_tution_fees+$housing_loan+$insurance_pre_paid+$public_provident_fund+$national_saving_certificate+$united_link_insurance+$mutual_fund;

        if($temp_final_ded<=150000)
        {
            $total_salr=$total_salr-$temp_final_ded-$sd;
        }
        else
        {
            $total_salr=$total_salr-150000-$sd;
        }

        if($nps<=150000)//slab changed to 150000 from 50000
        {
            $total_salr=$total_salr-$nps;
        }
        else
        {
            $total_salr=$total_salr-150000;
        }
        drupal_set_message("Total Salary::".$total_salr);
        drupal_set_message("Tax Payable::".$final_tax);
	}
}

?>