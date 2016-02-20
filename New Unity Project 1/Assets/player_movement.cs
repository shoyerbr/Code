using UnityEngine;
using System.Collections;

public class player_movement : MonoBehaviour {
	public int score = 0;
	//public Ui scoreText;
	public float max_speed = 5f;
	Vector3 velocity = Vector3.zero;
	public float forward = 1f;
	public Vector3 bounce;
	public Vector3 turn_left;
	public Vector3 turn_right;
	public Vector3 grav;
	bool did_click = false;
	bool left = false;
	bool right = false;
	public float angle;
	public bool Done = false;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKey("space"))
			did_click = true;
		if (Input.GetKey("left"))
			left = true;
		if (Input.GetKey("right"))
			right = true;
	}
	void scores(int add)
	{
		score += add;
	}
	void FixedUpdate()
	{
		if (!Done) {
			velocity.z = forward;
			if (transform.position.y > 0) 
				velocity += grav;
			else {
				velocity.y = 0;

			}
			if (did_click) {
				did_click = false;
				velocity.y += 1;
			}
			if (left) {
				left = false;
				velocity += turn_left;
			} else
				if (right) {
				right = false;
				velocity += turn_right;
			} else 
				velocity.x = 0;
			if (velocity.y >= max_speed)
				velocity.y = max_speed;
			if (velocity.x >= 8)
				velocity.x = 8;
			if (velocity.x <= -8)
				velocity.x = -8;
			if (transform.position.y <= 6) {
				velocity.y = 0;
				velocity.x = 0;
				velocity.z -= 8;
				Done = true;
			}
			if (transform.position.y >= 100)
				velocity.y = -1;
			if (transform.position.x >= 20)
				velocity.x = -1;
			if (transform.position.x <= -20)
				velocity.x = 1;
			transform.position += velocity * Time.deltaTime;
			angle = -90 - velocity.y * 7;
			if (angle > -55)
				angle = -55;
			transform.localEulerAngles = new Vector3 (angle, 0, velocity.x * 3);
			//scoreText.text = "Score: " + score;
		} else
			Debug.LogError ("lost");
	}
	
}
