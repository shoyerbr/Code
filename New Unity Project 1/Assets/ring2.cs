using UnityEngine;
using System.Collections;

public class ring2 : MonoBehaviour {
	public GameObject foo;
	public int score;
	public 	player_movement temp;
	void Start () {
		transform.position = foo.transform.position + new Vector3 (Random.Range(-10.0F, 10.0F), Random.Range(-10.0F, 10.0F), 20);
	}

	void Update ()
	{
		GameObject blah = GameObject.FindGameObjectWithTag ("Player");
		if (temp.transform.position.z > (transform.position.z + 2.5))
			temp.Done = true;
		if (Mathf.Abs(transform.position.x - blah.transform.position.x) < 4 && Mathf.Abs(transform.position.z - blah.transform.position.z) < 2.5 && Mathf.Abs(transform.position.y - blah.transform.position.y) < 4)
		{
			float num = (10-(temp.score * .1f));
			if (num < 1)
				num = 1;
			Vector3 Bar = foo.transform.position + new Vector3 (Random.Range(-10.0F, 10.0F), Random.Range(-10.0F, 10.0F), num);
			if (Bar.x > 20)
				Bar.x = 40 - Bar.x;
			if (Bar.x < -20)
				Bar.x = -40 - Bar.x;
			if (Bar.y < 6)
				Bar.y = Bar.y + 10;
			if (Bar.y > 100)
				Bar.y = 200 - Bar.y;
			transform.position = Bar;
			temp.score += 1;
			Debug.LogError (temp.score);
		}
	}
}
