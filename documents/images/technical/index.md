```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>QSP</title>
</head>
<body>

    <h1>Shortest Path</h1>
    <h2>Simplify Response</h2>
    <form action="http://localhost:8080/api/shortest-path/" method="get">
        <label for="landmark_1_simplify">Landmark 1:</label>
        <input type="text" id="landmark_1_simplify" name="landmark_1" required>
        <br>
        <label for="landmark_2_simplify">Landmark 2:</label>
        <input type="text" id="landmark_2_simplify" name="landmark_2" required>
        <br>
        <input type="submit" value="Submit">
    </form>

    <h2>JSON Response</h2>
    <form action="http://localhost:8080/api/shortest-path/json" method="get">
        <label for="landmark_1_json">Landmark 1:</label>
        <input type="text" id="landmark_1_json" name="landmark_1" required>
        <br>
        <label for="landmark_2_json">Landmark 2:</label>
        <input type="text" id="landmark_2_json" name="landmark_2" required>
        <br>
        <input type="submit" value="Submit">
    </form>

    <h2>XML Response</h2>
    <form action="http://localhost:8080/api/shortest-path/xml" method="get">
        <label for="landmark_1_xml">Landmark 1:</label>
        <input type="text" id="landmark_1_xml" name="landmark_1" required>
        <br>
        <label for="landmark_2_xml">Landmark 2:</label>
        <input type="text" id="landmark_2_xml" name="landmark_2" required>
        <br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>
```
[Click here to go on: 12.5.1. HTML (prototype) of the technical specification](../../technical/technical_specification.md#1251-html-prototype)