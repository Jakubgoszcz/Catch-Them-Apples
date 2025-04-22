import matplotlib.pyplot as plt
import os
import glob

directory = "./testRes/"
jpg_files = glob.glob(os.path.join(directory, '*.jpg'))
for index, jpg_file in enumerate(jpg_files):
    new_name = f"test{index}.jpg"
    os.rename(jpg_file, new_name)
    print(f"Renamed '{jpg_file}' to '{new_name}'")
ix = 0
iy = 0

def onclick(event):
    global ix, iy
    ix, iy = event.xdata, event.ydata
    print(f'Point selected: x = {ix}, y = {iy}')
    plt.close()

testNumber = 0
for image_path in jpg_files:
    img = plt.imread(image_path)

    plt.imshow(img)
    plt.title('Click on a point')
    plt.gca().set_axis_off()

    cid = plt.gcf().canvas.mpl_connect('button_press_event', onclick)

    plt.show()

    with open(f'test{testNumber}.txt', 'w') as file:
        file.write(f'{ix} {iy}')
        print('Point saved to selected_point.txt')

    print(f"""
    TEST_CASE("Test{testNumber}","[recognition]")
    {{
        auto point = processImage(cv::imread("./testRes/test{testNumber}.jpg"), blueStart, blueEnd);
        std::ifstream f("./testRes/test{testNumber}.txt");
        int x, y;
        f >> x >> y;
        double distance = std::sqrt(std::pow(point.x-x,2) + std::pow(point.y-y,2));
        CHECK(distance < threshold);
    }}
    """,file=open("test.cpp", "a"))
    testNumber += 1
print("Finished generating tests.")
