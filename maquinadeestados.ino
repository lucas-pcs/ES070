

char senhaMestre[ ] = {'0','1','0','2','0','3','\0'};
char senha[ ] = {'0','1','0','2','0','3','\0'};
char senhaD[ ];
char tecla;

void maquinaDeEstados(char tecla){
  switch(Estado){
    case ESPERA:
      switch(tecla){
        case 'A':
          Estado = CADASTRO;
          break;
        case 'B':
          Estado = 
      }
  }
  
  
  if(Estado == ESPERA){
    if(tecla == 'A'){
      Estado = CADASTRO;
    }
    if((senha[0] == senhaMestre[0]) &&(senha[1] == senhaMestre[1]) && (senha[2] == senhaMestre[2]) && (senha[3] == senhaMestre[3])&& (senha[4] == senhaMestre[4])&& (senha[5] == senhaMestre[5]) && (senha[6] == senhaMestre[6]) && (senha[7] == 'A')){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Digite a nova senha");
        while 1{
         senhaD = leSenha();
         if(strlen(senhaD) == 8){
          break;
         }
         //CADASTRA NOVA SENHA (senhaD)
        }
    }else if((senha[0] == senhaMestre[0]) &&(senha[1] == senhaMestre[1]) && (senha[2] == senhaMestre[2]) && (senha[3] == senhaMestre[3])&& (senha[4] == senhaMestre[4])&& (senha[5] == senhaMestre[5]) && (senha[6] == senhaMestre[6]) && (senha[7] == 'A')){
  }





  
}





















  if((palavra[0] == senha[0]) &&(palavra[1] == senha[1]) && (palavra[2] == senha[2]) && (palavra[3] == senha[3])&& (palavra[4] == senha[4])&& (palavra[5] == senha[5]) && (palavra[6] == senha[6]))
 //____________________________________________________________________________________________________________________ 
  {
     lcd.clear();
     lcd.print("Senha Correta !");
     delay (600);
     lcd.clear();
     tone(buzzer,2500);
     delay(100);
     tone(buzzer,900);
     delay(100);
     noTone(buzzer); 
          
      
           lcd.print("Porta Aberta");
             motor1.write(120); 
     digitalWrite(Led_verde,HIGH);
     digitalWrite(Led_vermelho,LOW);
           delay(6000);
         
           lcd.clear();
           lcd.print("Trave a porta");
            
      tone(buzzer,300);
     delay(500);
     noTone(buzzer);
     delay(500);
           digitalWrite(Led_vermelho,LOW);
           digitalWrite(Led_verde,HIGH);
           contador = 0;
          
   
    
     
     
      }//________________________________________________________________________________________________________________________
     else
     {lcd.clear();
     lcd.print("Senha incorreta!");
  
     tone(buzzer,300);
     delay(500);
     noTone(buzzer);
     delay(500);
     tone(buzzer,300);
     delay(100);
     noTone(buzzer);
     delay(500);
     delay(2000);
   
           contador = 0;
     lcd.clear();
     lcd.print("Digite a Senha: ");


     }
