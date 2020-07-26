package com.example.firebase_led_control;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TableLayout;
import android.widget.TextView;

import com.example.firebase_led_control.R;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    Button btnOnOff;
    TextView textView;

    //애니메이션 추가
    Animation mAnim1;

    String status = "";

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference myRef = database.getReference("RED_LED_STATUS");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //애니메이션 관련
        mAnim1 = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.scale);
        mAnim1.setInterpolator(getApplicationContext(), android.R.anim.accelerate_interpolator);

        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.textView);
        btnOnOff = (Button) findViewById(R.id.btnOnOFF);

        setTitle("LED Controller");

        this.InitializeView();
        this.SetListener();
    }

    public void InitializeView() {
        textView.setText(myRef.getKey());
    }


    public void SetListener() {
        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) { //데이터가 변경될떄 실행
                String ledState = (String) dataSnapshot.getValue(); // 데이터 가져오기
                textView.setText("LED " + ledState);
                status = ledState;

                if (ledState.equals("OFF")) { // Firebase에서 읽어온 값이 'OFF'
                    btnOnOff.setBackgroundResource(R.drawable.bulb_off);
                } else {                      // Firebase에서 읽어온 값이 'ON'
                    btnOnOff.setBackgroundResource(R.drawable.bulb_on);
                }

            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });


        btnOnOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) { // 버튼 클릭했을때 애니메이션 및 이미지 변경

                if (status.equals("ON")) { // 'ON'일때
                    view.startAnimation(mAnim1);
                    textView.setTextColor(Color.WHITE);
                    myRef.setValue("OFF");
                } else {                   // 'OFF'일때
                    view.startAnimation(mAnim1);
                    textView.setTextColor(Color.WHITE);
                    myRef.setValue("ON");
                }

            }
        });
    }
}