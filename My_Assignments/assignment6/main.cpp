/*
 * CS106L Assignment 6: Explore Courses
 * Created by Haven Whitney with modifications by Jacob Roberts-Baca and Fabio
 * Ibanez.
 */

#include <algorithm>
#include <type_traits>
#include <vector>
#include <optional>

/** STUDENT_TODO: You will need to include a relevant header file here! */

#include "autograder/utils.hpp"

/**
 * A course. This should be familiar from Assignment 1!
 */
struct Course
{
  std::string title;
  std::string number_of_units;
  std::string quarter;

  /**
   * You don't have to ignore this anymore! We're defining the `==` operator for
   * the Course struct.
   */
  bool operator==(const Course& other) const
  {
    return title == other.title && number_of_units == other.number_of_units &&
           quarter == other.quarter;
  }
};

class CourseDatabase
{
public:
  CourseDatabase(std::string filename)
  {
    auto lines = read_lines(filename);
    std::transform(lines.begin(),
                   lines.end(),
                   std::back_inserter(courses),
                   [](std::string line) {
                     auto parts = split(line, ',');
                     return Course{ parts[0], parts[1], parts[2] };
                   });
  }

  /**
   * Finds a course in the database with the given title, if it exists.
   * @param course_title The title of the course to find.
   * @return An optional containing the course if found, or empty if not found.
   */
  std::optional<Course> find_course(std::string course_title)
  {
    auto it = std::find_if(courses.begin(), courses.end(),
                          [&course_title](const Course& course) {
                              return course.title == course_title;
                          });
    
    if (it != courses.end()) {
        return *it;
    }
    return std::nullopt;
  }

private:
  std::vector<Course> courses;
};

int
main(int argc, char* argv[])
{
  static_assert(
    !std::is_same_v<std::invoke_result_t<decltype (&CourseDatabase::find_course), 
                      CourseDatabase, std::string>,
                    FillMeIn>,
    "You must change the return type of CourseDatabase::find_course to "
    "something other than FillMeIn.");

  if (argc == 2) {
    CourseDatabase db("autograder/courses.csv");
    auto course = db.find_course(argv[1]);
    
    // 使用monadic操作处理输出
    std::string output = course
        .transform([](const Course& c) -> std::string {
            return "Found course: " + c.title + "," + c.number_of_units + "," + c.quarter;
        })
        .value_or("Course not found.");

    std::cout << output << std::endl;
    return 0;
  }
  
  return run_autograder();
}