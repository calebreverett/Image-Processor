#include <iostream>
#include "Image.h"
using namespace std;

int main() {
    Image layer1("input/layer1.tga");
    Image pattern1("input/pattern1.tga");
    Image car("input/car.tga");
    Image layer2("input/layer2.tga");
    Image pattern2("input/pattern2.tga");
    Image text("input/text.tga");
    Image circles("input/circles.tga");
    Image layer_green("input/layer_green.tga");
    Image layer_blue("input/layer_blue.tga");
    Image layer_red("input/layer_red.tga");
    Image text2("input/text2.tga");
    Image example1("examples/EXAMPLE_part1.tga");
    Image example2("examples/EXAMPLE_part2.tga");
    Image example3("examples/EXAMPLE_part3.tga");
    Image example4("examples/EXAMPLE_part4.tga");
    Image example5("examples/EXAMPLE_part5.tga");
    Image example6("examples/EXAMPLE_part6.tga");
    Image example7("examples/EXAMPLE_part7.tga");
    Image example8_r("examples/EXAMPLE_part8_r.tga");
    Image example8_g("examples/EXAMPLE_part8_g.tga");
    Image example8_b("examples/EXAMPLE_part8_b.tga");
    Image example9("examples/EXAMPLE_part9.tga");
    Image example10("examples/EXAMPLE_part10.tga");
    Image exampleEC("examples/EXAMPLE_extracredit.tga");

    Image output1 = pattern1;
    output1.Multiply(layer1);
    output1.PrintFile("output/part1.tga");
    if(output1 == example1){
        cout << "Test 1: Completed" << endl;
    }
    else{
        cout << "Test 1: Failed" << endl;
    }

    Image output2 = car;
    output2.Subtract(layer2);
    output2.PrintFile("output/part2.tga");
    if(output2 == example2){
        cout << "Test 2: Completed" << endl;
    }
    else{
        cout << "Test 2: Failed" << endl;
    }


    Image output3 = pattern2;
    output3.Multiply(layer1);
    output3.Screen(text);
    output3.PrintFile("output/part3.tga");
    if(output3 == example3){
        cout << "Test 3: Completed" << endl;
    }
    else{
        cout << "Test 3: Failed" << endl;
    }


    Image output4 = circles;
    output4.Multiply(layer2);
    output4.Subtract(pattern2);
    output4.PrintFile("output/part4.tga");
    if(output4 == example4){
        cout << "Test 4: Completed" << endl;
    }
    else{
        cout << "Test 4: Failed" << endl;
    }

    Image output5 = pattern1;
    output5.Overlay(layer1);
    output5.PrintFile("output/part5.tga");
    if(output5 == example5){
        cout << "Test 5: Completed" << endl;
    }
    else{
        cout << "Test 5: Failed" << endl;
    }

    Image output6 = car;
    output6.Add(0, 200, 0);
    output6.PrintFile("output/part6.tga");
    if(output6 == example6){
        cout << "Test 6: Completed" << endl;
    }
    else{
        cout << "Test 6: Failed" << endl;
    }

    Image output7 = car;
    output7.Scale(0, 1, 4);
    output7.PrintFile("output/part7.tga");
    if(output7 == example7){
        cout << "Test 7: Completed" << endl;
    }
    else{
        cout << "Test 7: Failed" << endl;
    }

    Image output8_r = car;
    output8_r.Separate("red");
    Image output8_g = car;
    output8_g.Separate("green");
    Image output8_b = car;
    output8_b.Separate("blue");
    output8_r.PrintFile("output/part8_r.tga");
    output8_g.PrintFile("output/part8_g.tga");
    output8_b.PrintFile("output/part8_b.tga");
    if(output8_r == example8_r && output8_g == example8_g && output8_b == example8_b){
        cout << "Test 8: Completed" << endl;
    }
    else{
        cout << "Test 8: Failed" << endl;
    }

    Image output9 = layer_blue;
    output9.Combine(layer_blue, layer_green, layer_red);
    output9.PrintFile("output/part9.tga");
    if(output9 == example9){
        cout << "Test 9: Completed" << endl;
    }
    else{
        cout << "Test 9: Failed" << endl;
    }

    Image output10 = text2;
    output10.Flip();
    output10.PrintFile("output/part10.tga");
    if(output10 == example10){
        cout << "Test 10: Completed" << endl;
    }
    else{
        cout << "Test 10: Failed" << endl;
    }

    Image extraCredit = car;
    extraCredit.Expand(2);
    extraCredit.Include(text, pattern1, car, circles);
    extraCredit.PrintFile("output/extracredit.tga");
    if(extraCredit == exampleEC){
        cout << "Extra Credit: Completed" << endl;
    }
    else{
        cout << "Extra Credit: Failed" << endl;
    }
}
