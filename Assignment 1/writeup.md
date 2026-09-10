## Course Entry Survey
Done
## Identifying Effective Strategies for Learning
1. Choose a moment in your educational career (it could be an assignment or a full course) where learning went really well. What strategies did you employ that worked particularly well (e.g., working with others, trying work on your own before asking a friend, going to office hours)?
   
During Discrete Math something that helped a lot was going to office hours to ask about conceptual stuff to make sure i understood the concept properly. I went to the office hours and asked if my mental model was correct and find out when it was wrong and this helped me learn.
2. Similar to (1), which sorts of strategies have led to either less effective learning or less enjoyment of the learning experience. Feel free to describe a few examples of what doesn’t work for you.
   
I found that asking AI to explain things simply has not worked particularly well because when it explains something, a lot of context is lost and it produces something that sounds like a good explanation but does not help me understand the original document. However, I found it more useful for targeted questions such as. What function can I use in a specific case.
3. As this course is foundational for many aspects of computer science, the problems in this class can be easily solved with modern AI systems (e.g., ChatGPT, Gemini, etc.). One of my foundational assumptions is the process of grappling with a problem helps you internalize the important concepts, gives you more insight into how the tools you are learning can be applied in other contexts, helps you more realistically assess your own abilities, and helps you learn to better communicate your knowledge to others. Particular methods of using AI (e.g., prompting the AI to provide answers to questions and thoughtlessly copying the answers) are unlikely to achieve the learning goals articulated previously. Do you agree with this framing? How are you thinking about AI tools with respect to this course?
      
I agree with this framing and I want to learn the actual content. I will probably not use AI for anything for this class aside from some help refreshing coding syntax I had forgotten. I also might use it to stress testing project ideas before I start implementing them.
4.  What strategies will you use in this course to be successful? With respect to AI, what principles or strategies will you use during this course.
    
I will probably just take notes and aim to go to office hours and also finish assignments early so I have time to check over them. With respect to AI, In this class I want to program everything by hand and use AI minimally in this course so I can learn the concepts behind the code I write. I also want to use it minimally for debugging so I get more practice reading code and finding errors quickly. 

5. What do you think of some of  [the proposed activities for the oral quizzes](https://olin.instructure.com/courses/940/pages/course-policies-and-structure)? Are these activities ones that would give you helpful feedback as to how you are performing with respect to the course material? Would you add or subtract any of the proposed activities?

I think these activities would give helpful feedback on how I'm performing. For me, the most helpful one would be being given a problem on the spot and being asked to solve it. It would test our ability to answer a question quickly and select appropriate data structures. I feel like this would be helpful for me to get better at.
I also think being given an implementation of an algorithm and working through whether it's correct or not would be very relevant in the modern day for checking AI outputs meticulously, and I think more practice on it would be better. Giving a whiteboard talk would also be helpful. Teaching is a useful way to learn things better.
I think explaining a section of code from a submitted assignment would be the least useful, at least for me, because I find that easier to do than the other three.
Another oral I think is interesting is asking open-ended questions and, for me, asking questions to narrow down what needs to actually be implemented depending on the use case, as we are often working with incomplete information and it is a useful skill to know what information is useful before implementing something.
One concern I have is how I would prepare for these assessments. I would hope mock tests and problem examples would be provided beforehand so I can prepare better for an oral.

6. How can the teaching team support you?
Probably just hosting office hours before assignment deadlines and also providing Oral exam practice examples.
## Hello World
Tour Finished

1. What features do you like about Kotlin?

I like how there is a double and a triple and a list and a mutable list and also how you can state if a variable changes or not. I also like how the types remain static. This allows the code editor to catch many errors before you run the code which makes the end result a lot easier to debug.

2. Are there things you were expecting to find that you haven’t?

I was expecting it would convert types by itself like python but you have to manually convert them. I am used to python so this was surprising to me. However I realize it is a lot easier to read the code because of this.

3. What questions do you have?

I am curious about learning more about kotlin like what different libraries are out there and how to use them. I am also curious about the difference between a float and a double and when you should use which.
4. Try using the debugger (see the Getting Set with Kotlin page) for some very basic information on the debugger. Do you have experience using interactive debuggers like this one? Were you able to successfully launch the debugger?

I was able to get it to work. It did help a lot with understanding what the program was doing and where it was failing.

## Translating Your Old Code

Writeup that describes the purpose of the code and how you found the process of translating the code to Kotlin (or the language you wind up choosing). Feel free to touch on the good, the bad, and the ugly.

The code was originally written in Python and is available at PortingCodeToKotlinOriginal.py. The translated code and its unit tests are in src/PortingCodeToKotlinTranslated.kt.

The original code was part of an evaluation harness for an object detection model. The model outputted a bounding box in the form x1, y1, x2, y2, and this would be compared to the ground truth. The values were frequently normalized, so they were usually in the 0–1 range. The normalization ensures that if the image resolution changes, the coordinates can still be found without knowing the original height and width of the image. The code includes one function called iou, which calculates the degree of overlap between the two bounding boxes. This is used as a metric that measures the accuracy of the bounding boxes produced by the ML model. The function first checks if both inputs are in the right format (4 values), and if not, it returns 0. It assumes the boxes are rectangular. To measure this, it uses the intersection/union formula, which is the area common between the two boxes over the combined area of both of the boxes.

I tried to pick a snippet of code that did not use any external libraries. However, I did find out that some math functions available by default in Python needed the math function in Kotlin. I was able to successfully translate it. I like the way types are defined in Kotlin. It made the program much faster to debug than it took in Python. I found a lot of the math functions were quite similar; however, the list formatting changed. However, I think the tests looked less clean than in Python, but this might be improved by finding out if there is a more efficient way to declare a number as a float.

## Implementing Meeting Scheduler

both programs and unit tests are in src/FindMeetingConflicts.kt

Brute Force: $O(n^2)$ as there are 2 for loops that iterate over the meetings
With Sort: Since it sorts the list and then loops over it one more time to check for conflicts. so it would be $n + n \log(n)$ or $O(n \log(n))$